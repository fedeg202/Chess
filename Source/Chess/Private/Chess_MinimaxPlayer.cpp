// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_MinimaxPlayer.h"
#include "ChessGameMode.h"
#include "Chess_PlayerController.h"


AChess_MinimaxPlayer::AChess_MinimaxPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	GameInstance = Cast<UChess_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	Color = EColor::NONE;
}

void AChess_MinimaxPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AChess_MinimaxPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChess_MinimaxPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AChess_MinimaxPlayer::OnTurn()
{
	if (ChessHUD == nullptr)
	{
		AChess_PlayerController* PC = Cast<AChess_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		ChessHUD = PC->ChessHUD;
	}

	IsMyTurn = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MinimaxPlayer Turn"));
	GameInstance->SetTurnMessage("MinimaxPlayer in Turn");

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {

		FCoupleTile Tiles = FindBestMove();
		bool b_eatFlag = false;
		APiece* Piece = Tiles.Tile1->GetOnPiece();

		if (Tiles.Tile2->GetTileStatus() == ETileStatus::OCCUPIED)
		{
			Piece->Eat(Tiles.Tile2, ChessBoard);
			b_eatFlag = true;
		}

		else Piece->Move(Tiles.Tile2, ChessBoard->GetGameField());

		AChessGameMode* GameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());

		IsMyTurn = false;

		if (!ChessBoard->CheckPawnPromotion(Piece))
		{
			ChessHUD->AddMoveButtonToTheHistoryScrollBox(ChessBoard->CreateMoveString(Piece, Tiles, b_eatFlag, false), Color);
			ChessBoard->AddMove(FMove(Tiles, Color, b_eatFlag, false));
			GameMode->TurnNextPlayer();
		}
		else
		{
			ChessHUD->AddMoveButtonToTheHistoryScrollBox(ChessBoard->CreateMoveString(Piece, Tiles, b_eatFlag, true), Color);
			ChessBoard->AddMove(FMove(Tiles, Color, b_eatFlag, false));
			GameMode->HandlePawnPromotion(EPieceColor::BLACK, EPieceName::QUEEN);
		}
	}, 1, false);
}

void AChess_MinimaxPlayer::OnWin()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MinimaxPlayer won!"));
	GameInstance->SetTurnMessage(TEXT("MinimaxPlayer Wins"));
}

void AChess_MinimaxPlayer::OnLose()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MinimaxPlayer lose!"));
	GameInstance->SetTurnMessage(TEXT("MinimaxPlayer Loses!"));
}

void AChess_MinimaxPlayer::OnCheck()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MinimaxPlayer is in check"));
	GameInstance->SetTurnMessage(TEXT("MinimaxPlayer in check"));
	OnTurn();
}

void AChess_MinimaxPlayer::OnStalemate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MinimaxPlayer in stalemate"));
	GameInstance->SetTurnMessage(TEXT("MinimaxPlayer in stalemate"));
}

void AChess_MinimaxPlayer::OnCheckmate()
{
	this->OnLose();
}

int32 AChess_MinimaxPlayer::EvaluateBoard()
{
	int32 Value = 0;
	ETileOwner OppositeColor;
	ETileOwner SameColor;

	ChessBoard->UpdateAllMoveBYColor(ETileOwner::BLACK);
	ChessBoard->UpdateAllMoveBYColor(ETileOwner::WHITE);

	bool WhiteCheck = ChessBoard->CheckOnCheck(ETileOwner::WHITE);
	bool BlackCheck = ChessBoard->CheckOnCheck(ETileOwner::BLACK);

	bool WhiteStale = ChessBoard->CheckOnStalemate(ETileOwner::WHITE);
	bool BlackStale = ChessBoard->CheckOnStalemate(ETileOwner::BLACK);




	if (Color == EColor::BLACK)
	{
		SameColor = ETileOwner::BLACK;
		OppositeColor = ETileOwner::WHITE;

		if (WhiteCheck && WhiteStale) return 1000;
		else if (BlackCheck && BlackStale) return -1000;

		if (BlackCheck) Value += -5;
		if (WhiteCheck) Value += +5;
	}
	else
	{
		SameColor = ETileOwner::WHITE;
		OppositeColor = ETileOwner::BLACK;

		if (BlackCheck && BlackStale) return 1000;
		else if (WhiteCheck && WhiteStale) return -1000;

		if (WhiteCheck) Value += -5;
		if (BlackCheck) Value += +5;
	}
		

	Value += ChessBoard->GetAllSelectableMovesByColor(SameColor).Num() - (ChessBoard->GetAllSelectableMovesByColor(OppositeColor).Num());

	int32 tmp_sumWhite = 0;
	for (int32 i = 0; i < ChessBoard->GetWhitePieces().Num(); i++)
	{
		if (ChessBoard->GetWhitePieces()[i]->AvaibleMoves(ChessBoard).Num() == 0)
			tmp_sumWhite += ChessBoard->GetWhitePieces()[i]->GetValue();
	}

	int32 tmp_sumBlack = 0;
	for (int32 i = 0; i < ChessBoard->GetBlackPieces().Num(); i++)
	{
		if (ChessBoard->GetBlackPieces()[i]->AvaibleMoves(ChessBoard).Num() == 0)
			tmp_sumBlack += ChessBoard->GetBlackPieces()[i]->GetValue();
	}

	if (Color == EColor::BLACK)
		Value += tmp_sumBlack - tmp_sumWhite;
	else 
		Value += tmp_sumWhite - tmp_sumBlack;

	return Value;

}

int32 AChess_MinimaxPlayer::AlfaBetaMiniMax(int32 Depth,int32 alpha, int32 beta, bool IsMax)
{
	if (Depth == 0) return EvaluateBoard();

	ETileOwner SameColor = ETileOwner::BLACK;
	ETileOwner OppositeColor = ETileOwner::WHITE;

	APiece* EventualPromotedPawn;
	AQueen* Queen = nullptr;
	bool b_PawnPromotion = false;

	APiece* tmp_Piece;
	if (IsMax)
	{
		int32 Value = -MaxValue;
		ChessBoard->UpdateAllMoveBYColor(SameColor);
		TArray <FCoupleTile> Moves = ChessBoard->GetAllMovesByColor(SameColor);

		if (Moves.Num() == 0) return EvaluateBoard();

		for (int32 i = 0; i < Moves.Num(); i++)
		{
			tmp_Piece = ChessBoard->VirtualMove(Moves[i]);

			b_PawnPromotion = ChessBoard->CheckPawnPromotion(SameColor);
			if (b_PawnPromotion)
			{
				EventualPromotedPawn = Moves[i].Tile2->GetOnPiece();
				Queen = NewObject<AQueen>(this);		 Queen->SetGridPosition(Moves[i].Tile2->GetGridPosition());
				ChessBoard->GetPiecesByColor(SameColor).Remove(EventualPromotedPawn);
				ChessBoard->GetPiecesByColor(SameColor).Add(Queen);
				Moves[i].Tile2->SetOnPiece(Queen);
			}

			Value = FMath::Max(Value, AlfaBetaMiniMax(Depth - 1, alpha, beta, false));
			ChessBoard->VirtualUnMove(Moves[i],tmp_Piece);

			if (b_PawnPromotion)
			{
				ChessBoard->GetPiecesByColor(SameColor).Remove(Queen);
				ChessBoard->GetPiecesByColor(SameColor).Add(EventualPromotedPawn);
				Moves[i].Tile2->SetOnPiece(EventualPromotedPawn);
				Queen->Destroy();
			}

			//if (Value >= beta) return Value;
			//alpha = FMath::Max(alpha, Value);
		}
		return Value;
	}
	else
	{
		int32 Value = MaxValue;
		ChessBoard->UpdateAllMoveBYColor(OppositeColor);
		TArray <FCoupleTile> Moves = ChessBoard->GetAllMovesByColor(OppositeColor);
		
		if (Moves.Num() == 0) return EvaluateBoard();

		for (int32 i = 0; i < Moves.Num(); i++)
		{
			tmp_Piece = ChessBoard->VirtualMove(Moves[i]);
			b_PawnPromotion = ChessBoard->CheckPawnPromotion(SameColor);
			if (b_PawnPromotion)
			{
				EventualPromotedPawn = Moves[i].Tile2->GetOnPiece();
				Queen = NewObject<AQueen>(this);		 Queen->SetGridPosition(Moves[i].Tile2->GetGridPosition());
				ChessBoard->GetPiecesByColor(SameColor).Remove(EventualPromotedPawn);
				ChessBoard->GetPiecesByColor(SameColor).Add(Queen);
				Moves[i].Tile2->SetOnPiece(Queen);
			}

			Value = FMath::Min(Value, AlfaBetaMiniMax(Depth - 1, alpha, beta, true));
			ChessBoard->VirtualUnMove(Moves[i], tmp_Piece);

			if (b_PawnPromotion)
			{
				ChessBoard->GetPiecesByColor(SameColor).Remove(Queen);
				ChessBoard->GetPiecesByColor(SameColor).Add(EventualPromotedPawn);
				Moves[i].Tile2->SetOnPiece(EventualPromotedPawn);
				Queen->Destroy();
			}

			//if (Value <= alpha) return Value;
			//beta = FMath::Min(alpha, Value);
			
		}
		return Value;
	}

}

FCoupleTile AChess_MinimaxPlayer::FindBestMove()
{
	FCoupleTile BestMove;
	int32 BestVal = -(MaxValue+1);
	ETileOwner SameColor = ETileOwner::BLACK;
	APiece* tmp_Piece;
	APiece* EventualPromotedPawn;
	AQueen* Queen = nullptr;
	bool b_PawnPromotion = false;
	TArray <FCoupleTile> Moves = ChessBoard->GetAllMovesByColor(SameColor);

	for (int32 i = 0; i < Moves.Num(); i++)
	{
		tmp_Piece = ChessBoard->VirtualMove(Moves[i]);
		b_PawnPromotion = ChessBoard->CheckPawnPromotion(SameColor);
		if (b_PawnPromotion)
		{
			EventualPromotedPawn = Moves[i].Tile2->GetOnPiece();
			Queen = NewObject<AQueen>(this);		 Queen->SetGridPosition(Moves[i].Tile2->GetGridPosition());
			ChessBoard->GetPiecesByColor(SameColor).Remove(EventualPromotedPawn);
			ChessBoard->GetPiecesByColor(SameColor).Add(Queen);
			Moves[i].Tile2->SetOnPiece(Queen);
		}
		
		int32 MoveVal = AlfaBetaMiniMax(MiniMaxDepth,-MaxValue,+MaxValue, false);
		ChessBoard->VirtualUnMove(Moves[i], tmp_Piece);
		if (b_PawnPromotion)
		{
			ChessBoard->GetPiecesByColor(SameColor).Remove(Queen);
			ChessBoard->GetPiecesByColor(SameColor).Add(EventualPromotedPawn);
			Moves[i].Tile2->SetOnPiece(EventualPromotedPawn);
			Queen->Destroy();
		}
		if (MoveVal > BestVal)
		{
			BestMove = Moves[i];
			BestVal = MoveVal;
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("AI minimax best val = %d"), BestVal));

	return BestMove;
}

