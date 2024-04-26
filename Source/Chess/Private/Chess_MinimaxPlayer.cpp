// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_MinimaxPlayer.h"
#include "ChessGameMode.h"
#include "Chess_PlayerController.h"
#include "Components/AudioComponent.h"

/**
 * @brief AChess_MinimaxPlayer class constructor
 *
 */
AChess_MinimaxPlayer::AChess_MinimaxPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	GameInstance = Cast<UChess_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	USceneComponent* NewRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	RootComponent = NewRootComponent;

	Color = EColor::NONE;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
}

/**
 * @brief Called when starting playing or on spawn
 *
 */
void AChess_MinimaxPlayer::BeginPlay()
{
	Super::BeginPlay();
}
/**
 * @brief Called every tick
 *
 */
void AChess_MinimaxPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
/**
 * @brief Called to setup the input component
 *
 */
void AChess_MinimaxPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
/**
 * @brief Called when the player start his turn
 *
 */
void AChess_MinimaxPlayer::OnTurn()
{
	if (ChessHUD == nullptr)
	{
		AChess_PlayerController* PC = Cast<AChess_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		ChessHUD = PC->ChessHUD;
	}

	if (SelectedPiece != nullptr)
		SelectedPiece->UnshowSelected();

	IsMyTurn = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MinimaxPlayer Turn"));
	if(!b_OnCheck) GameInstance->SetTurnMessage("MinimaxPlayer in Turn");

	int32 NumPieces = ChessBoard->GetBlackPieces().Num() + ChessBoard->GetWhitePieces().Num();
	if (NumPieces > 16) MiniMaxDepth = 2;
	else if (NumPieces > 8 && NumPieces <= 16) MiniMaxDepth = 3;
	else if (NumPieces <= 8) MiniMaxDepth = 4;

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {

		UE_LOG(LogTemp, Display, TEXT("MIniMax is goinggggg"));

		FCoupleTile Tiles = FindBestMove();
		bool b_eatFlag = false;
		SelectedPiece = Tiles.Tile1->GetOnPiece();
		SelectedPiece->ShowSelected();

		if (Tiles.Tile2->GetTileStatus() == ETileStatus::OCCUPIED)
		{
			SelectedPiece->Eat(Tiles.Tile2, ChessBoard);

			PlaySound(4);

			b_eatFlag = true;
		}

		else 
		{
			SelectedPiece->Move(Tiles.Tile2, ChessBoard->GetGameField());
			
			PlaySound(0);
		}

		AChessGameMode* GameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());

		IsMyTurn = false;

		if (!ChessBoard->CheckPawnPromotion(SelectedPiece))
		{
			ChessHUD->AddMoveButtonToTheHistoryScrollBox(ChessBoard->CreateMoveString(SelectedPiece, Tiles, b_eatFlag, false), Color);
			ChessBoard->AddMove(FMove(Tiles, Color, b_eatFlag, false));
			GameMode->TurnNextPlayer();
		}
		else
		{
			ChessHUD->AddMoveButtonToTheHistoryScrollBox(ChessBoard->CreateMoveString(SelectedPiece, Tiles, b_eatFlag, true), Color);
			ChessBoard->AddMove(FMove(Tiles, Color, b_eatFlag, false));
			GameMode->HandlePawnPromotion(EPieceColor::BLACK, EPieceName::QUEEN);
		}
	}, 1, false);
}

/**
 * @brief Called when the player win
 *
 */
void AChess_MinimaxPlayer::OnWin()
{
	if (SelectedPiece != nullptr)
		SelectedPiece->UnshowSelected();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MinimaxPlayer won!"));
	//GameInstance->SetTurnMessage(TEXT("MinimaxPlayer Wins"));
}

/**
 * @brief Called when the player lose
 *
 */
void AChess_MinimaxPlayer::OnLose()
{
	if (SelectedPiece != nullptr)
		SelectedPiece->UnshowSelected();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MinimaxPlayer lose!"));
	//GameInstance->SetTurnMessage(TEXT("MinimaxPlayer Loses!"));
}

/**
 * @brief Called when the player is in check
 *
 */
void AChess_MinimaxPlayer::OnCheck()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MinimaxPlayer is in check"));
	GameInstance->SetTurnMessage(TEXT("MinimaxPlayer in check"));
	OnTurn();
}

/**
 * @brief Called when the player is in stalemate or draw
 *
 */
void AChess_MinimaxPlayer::OnStalemate()
{
	if (SelectedPiece != nullptr)
		SelectedPiece->UnshowSelected();
	if (b_OnStalemate)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MinimaxPlayer in stalemate"));
		GameInstance->SetTurnMessage(TEXT("MinimaxPlayer in stalemate"));
		PlaySound(3);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Draw by repetition!"));
		GameInstance->SetTurnMessage(TEXT("Draw by repetition!"));
	}
}

/**
 * @brief Called when the player is on checkmate
 *
 */
void AChess_MinimaxPlayer::OnCheckmate()
{
	this->OnLose();
}

/**
 * @brief Method to evaluate the board for the minimax algorithm
 *
 */
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

	
	FString State = ChessBoard->GetChessboardStateString();

	if (ChessBoard->StateOccurrences.Contains(State))
	{
		if (ChessBoard->StateOccurrences[State] == 2) 
		{
			UE_LOG(LogTemp, Display, TEXT("Value tmp = 0"))
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Two occurences of the state already in, try not to go for the third"));
			return 0;
		}
	}


	if (Color == EColor::BLACK)
	{
		SameColor = ETileOwner::BLACK;
		OppositeColor = ETileOwner::WHITE;

		if (WhiteCheck && WhiteStale) 
		{
			UE_LOG(LogTemp, Display, TEXT("Value tmp = %d"), MaxValue);
			return MaxValue;
		}
		else if (BlackCheck && BlackStale)
		{
			UE_LOG(LogTemp, Display, TEXT("Value tmp = %d"), -MaxValue);
			return -MaxValue;
		}
		else if ((!WhiteCheck && WhiteStale) || (!BlackCheck && BlackStale)) {
			UE_LOG(LogTemp, Display, TEXT("Value tmp = 0"));
			return 0;
		}
	}
	else if (Color == EColor::WHITE)
	{
		SameColor = ETileOwner::WHITE;
		OppositeColor = ETileOwner::BLACK;

		if (BlackCheck && BlackStale)	return MaxValue;
		else if (WhiteCheck && WhiteStale) return -MaxValue;
		else if ((!WhiteCheck && WhiteStale) || (!BlackCheck && BlackStale)) return 0;
	}
		

	Value += ChessBoard->GetAllSelectableMovesByColor(SameColor).Num() - (ChessBoard->GetAllSelectableMovesByColor(OppositeColor).Num());

	int32 sumWhite = 0;
	for (int32 i = 0; i < ChessBoard->GetWhitePieces().Num(); i++)
	{
			sumWhite += ChessBoard->GetWhitePieces()[i]->GetValue();
	}

	int32 sumBlack = 0;
	for (int32 i = 0; i < ChessBoard->GetBlackPieces().Num(); i++)
	{
			sumBlack += ChessBoard->GetBlackPieces()[i]->GetValue();
	}

	if (Color == EColor::BLACK)
		Value += sumBlack - sumWhite;
	else
		Value += sumWhite - sumBlack;

	UE_LOG(LogTemp, Display, TEXT("Value tmp = %d"),Value);

	return Value;

}

/**
 * @brief Minimax algorithm to choose the best move of the AI
 * 
 * @param Depth depth of the algorithm
 * @param alpha alpha of the alphabeta pruning minimax algorithm
 * @param beta beta of the alphabeta pruning minimax algorithm
 * @param IsMax bool value to handle the min e max player alternation in the algorithm
 * 
 * @return Value obtained applying the algorithm
 */
int32 AChess_MinimaxPlayer::AlfaBetaMiniMax(int32 Depth,int32 alpha, int32 beta, bool IsMax)
{
	if (Depth == 0) return EvaluateBoard();

	FString State = ChessBoard->GetChessboardStateString();
	
	if (ChessBoard->StateOccurrences.Contains(State))
	{
		if (ChessBoard->StateOccurrences[State] == 2)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Try to avoid the draw by repetition"));
			return 0;
		}
	}

	ETileOwner SameColor = ETileOwner::BLACK;
	ETileOwner OppositeColor = ETileOwner::WHITE;

	APiece* EventualPromotedPawn = nullptr;
	AQueen* Queen = nullptr;
	bool b_PawnPromotion = false;

	APiece* tmp_Piece;
	if (IsMax)
	{
		//max is playing with the blacks
		int32 Value = -(MaxValue*10);
		ChessBoard->UpdateAllMoveBYColor(SameColor);
		TArray <FCoupleTile> Moves = ChessBoard->GetAllSelectableMovesByColor(SameColor,true);

		if (Moves.Num() == 0)
		{
			UE_LOG(LogTemp, Display, TEXT("Max is playing no moves avaible,next value is the evaluated and returned one"));
			return EvaluateBoard();
		}

		for (int32 i = 0; i < Moves.Num(); i++)
		{
			//Do the move ("Virtually" because the actors doesn't moves but only changes the state of the chessboard)
			tmp_Piece = ChessBoard->VirtualMove(Moves[i]);

			b_PawnPromotion = ChessBoard->CheckPawnPromotion(SameColor);
			if (b_PawnPromotion)
			{
				EventualPromotedPawn = Moves[i].Tile2->GetOnPiece();
				Queen = NewObject<ABlackQueen>(this);		 Queen->SetGridPosition(Moves[i].Tile2->GetGridPosition());
				ChessBoard->GetPiecesByColor(SameColor).Remove(EventualPromotedPawn);
				ChessBoard->GetPiecesByColor(SameColor).Add(Queen);
				Moves[i].Tile2->SetOnPiece(Queen);
			}

			Value = FMath::Max(Value, AlfaBetaMiniMax(Depth - 1, alpha, beta, false));

			if (b_PawnPromotion)
			{
				ChessBoard->GetPiecesByColor(SameColor).Remove(Queen);
				ChessBoard->GetPiecesByColor(SameColor).Add(EventualPromotedPawn);
				Moves[i].Tile2->SetOnPiece(EventualPromotedPawn);
				Queen->Destroy();
			}
			//Undo the move
			ChessBoard->VirtualUnMove(Moves[i],tmp_Piece);

			
			//Alpha beta pruning
			if (Value >= beta)
			{
				UE_LOG(LogTemp, Display, TEXT("Max is playing, alpha-beta pruning value = %d"), Value);
				return Value;
			}
			alpha = FMath::Max(alpha, Value);
		}

		UE_LOG(LogTemp, Display, TEXT("Max is playing, value = %d"),Value);

		return Value;
	}
	else
	{
		//Min is playing with the whites
		int32 Value = (MaxValue * 10)+1;
		ChessBoard->UpdateAllMoveBYColor(OppositeColor);
		TArray <FCoupleTile> Moves = ChessBoard->GetAllSelectableMovesByColor(OppositeColor,true);
		
		if (Moves.Num() == 0)
		{
			UE_LOG(LogTemp, Display, TEXT("Min is playing no moves avaible,next value is the evaluated and returned one"));
			return EvaluateBoard();
		}

		for (int32 i = 0; i < Moves.Num(); i++)
		{
			//Do the move ("Virtually" because the actors doesn't moves but only changes the state of the chessboard)
			tmp_Piece = ChessBoard->VirtualMove(Moves[i]);

			b_PawnPromotion = ChessBoard->CheckPawnPromotion(OppositeColor);
			if (b_PawnPromotion)
			{
				EventualPromotedPawn = Moves[i].Tile2->GetOnPiece();
				Queen = NewObject<AWhiteQueen>(this);		 Queen->SetGridPosition(Moves[i].Tile2->GetGridPosition());
				ChessBoard->GetPiecesByColor(OppositeColor).Remove(EventualPromotedPawn);
				ChessBoard->GetPiecesByColor(OppositeColor).Add(Queen);
				Moves[i].Tile2->SetOnPiece(Queen);
			}

			Value = FMath::Min(Value, AlfaBetaMiniMax(Depth - 1, alpha, beta, true));

			if (b_PawnPromotion)
			{
				ChessBoard->GetPiecesByColor(OppositeColor).Remove(Queen);
				ChessBoard->GetPiecesByColor(OppositeColor).Add(EventualPromotedPawn);
				Moves[i].Tile2->SetOnPiece(EventualPromotedPawn);
				Queen->Destroy();
			}
			//Undo the move
			ChessBoard->VirtualUnMove(Moves[i], tmp_Piece);

			//Alpha beta pruning
			if (Value <= alpha) 
			{
				UE_LOG(LogTemp, Display, TEXT("Min is playing, alpha-beta pruning value = %d"), Value);
				return Value;
			}
			beta = FMath::Min(alpha, Value);
			
		}

		UE_LOG(LogTemp, Display, TEXT("Min is playing, value = %d"), Value);

		return Value;
	}

}

/**
* @brief Method to obtain the best move computed with the minimax algorithm
*
* @return FCoupleTile struct with the two tiles of the best move computed
*/
FCoupleTile AChess_MinimaxPlayer::FindBestMove()
{
	FCoupleTile BestMove;
	int32 BestVal = -((MaxValue*10)+1);
	ETileOwner SameColor = ETileOwner::BLACK;
	APiece* tmp_Piece;
	APiece* EventualPromotedPawn;
	AQueen* Queen = nullptr;
	bool b_PawnPromotion = false;
	TArray <FCoupleTile> Moves = ChessBoard->GetAllSelectableMovesByColor(SameColor,true);

	for (int32 i = 0; i < Moves.Num(); i++)
	{
		tmp_Piece = ChessBoard->VirtualMove(Moves[i]);
		b_PawnPromotion = ChessBoard->CheckPawnPromotion(SameColor);
		if (b_PawnPromotion)
		{
			EventualPromotedPawn = Moves[i].Tile2->GetOnPiece();
			Queen = NewObject<ABlackQueen>(this);		 Queen->SetGridPosition(Moves[i].Tile2->GetGridPosition());
			ChessBoard->GetPiecesByColor(SameColor).Remove(EventualPromotedPawn);
			ChessBoard->GetPiecesByColor(SameColor).Add(Queen);
			Moves[i].Tile2->SetOnPiece(Queen);
		}
		
		int32 MoveVal = AlfaBetaMiniMax(MiniMaxDepth,-((MaxValue * 10)+1), (MaxValue * 10)+1, false);

		if (b_PawnPromotion)
		{
			ChessBoard->GetPiecesByColor(SameColor).Remove(Queen);
			ChessBoard->GetPiecesByColor(SameColor).Add(EventualPromotedPawn);
			Moves[i].Tile2->SetOnPiece(EventualPromotedPawn);
			Queen->Destroy();
		}

		ChessBoard->VirtualUnMove(Moves[i], tmp_Piece);
		
		if (MoveVal > BestVal)
		{
			BestMove = Moves[i];
			BestVal = MoveVal;

			UE_LOG(LogTemp, Display, TEXT("NewBest value = %d"), MoveVal);
		}
		else if (MoveVal == BestVal)
		{
			if (FMath::RandRange(0, 1))
			{
				BestMove = Moves[i];
				UE_LOG(LogTemp, Display, TEXT("SameBest value but change move, value = %d"), MoveVal);
			}
		}
			
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("AI minimax best val = %d"), BestVal));

	return BestMove;
}

/**
 * @brief Method to play a sound during game
 *
 * @param SoundIndex index of the sound to play (4 is the one of the eat or capture and there are 3 different sounds of the capture chosen randomly)
 */
void AChess_MinimaxPlayer::PlaySound(int32 SoundIndex)
{
	if (SoundIndex == 4)
		SoundIndex = FMath::RandRange(4, 6);

	if (SoundsToPlay[SoundIndex])
		AudioComponent->SetSound(SoundsToPlay[SoundIndex]);
	AudioComponent->Play();
}

