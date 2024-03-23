// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameMode.h"

#include "Engine.h"

#include "Chess_PlayerController.h"
#include "Chess_HumanPlayer.h"
#include "Chess_RandomPlayer.h"
//#include "TTT_MinimaxPlayer.h"

AChessGameMode::AChessGameMode()
{
	PlayerControllerClass = AChess_PlayerController::StaticClass();
	DefaultPawnClass = AChess_HumanPlayer::StaticClass();
}

void AChessGameMode::BeginPlay()
{

	Super::BeginPlay();

	IsGameOver = false;

	AChess_HumanPlayer* HumanPlayer = Cast<AChess_HumanPlayer>(*TActorIterator<AChess_HumanPlayer>(GetWorld()));

	if (ChessBoardClass != nullptr)
	{
		ChessBoard = GetWorld()->SpawnActor<AChessBoard>(ChessBoardClass);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Game Field is null"));
	}

	float CameraPosX = ((ChessBoard->GetGameField()->TileSize - 2) * ChessBoard->GetGameField()->Size)/2;
	FVector CameraPos(CameraPosX, CameraPosX, 1050.0f);
	HumanPlayer->SetActorLocationAndRotation(CameraPos, FRotationMatrix::MakeFromX(FVector(0, 0, -1)).Rotator());

	HumanPlayer->ChessBoard = ChessBoard;
	HumanPlayer->Color = EColor::WHITE;

	// Human player = 0
	Players.Add(HumanPlayer);
	
	AChess_PlayerController* PC = Cast<AChess_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UMainMenu* MainMenu = CreateWidget<UMainMenu>(PC, MainMenuClass);
	MainMenu->AddToPlayerScreen();
}

void AChessGameMode::TurnNextPlayer()
{
	CurrentReplayMoveIndex++;
	b_turnHumanPlayer = !b_turnHumanPlayer;
	ChessBoard->UpdateAllMoveBYColor(ETileOwner::WHITE);
	ChessBoard->UpdateAllMoveBYColor(ETileOwner::BLACK);

	if (b_turnHumanPlayer) 
	{
		CheckOnCheck(Players[0]);
		CheckOnStalemate(Players[0]);
		CheckOnCkeckmate(Players[0]);
		if (Players[0]->b_OnCheckmate) Players[0]->OnLose();
		else if (Players[0]->b_OnStalemate) Players[0]->OnStalemate();
		else if (Players[0]->b_OnCheck) Players[0]->OnCheck();
		else Players[0]->OnTurn();
	}
	else
	{
		CheckOnCheck(Players[1]);
		CheckOnStalemate(Players[1]);
		CheckOnCkeckmate(Players[1]);
		if (Players[1]->b_OnCheckmate) Players[0]->OnWin();
		else if (Players[1]->b_OnStalemate) Players[1]->OnStalemate();
		else if (Players[1]->b_OnCheck) Players[1]->OnCheck();
		else Players[1]->OnTurn();
	}
}

void AChessGameMode::StartGame(int32 Diff)
{
	if (Diff!=Difficulty)
		Difficulty = Diff;
	// Random Player
	auto* AI = GetWorld()->SpawnActor<AChess_RandomPlayer>(FVector(), FRotator());
	AI->ChessBoard = ChessBoard;
	AI->Color = EColor::BLACK;
	// MiniMax Player
	//auto* AI = GetWorld()->SpawnActor<ATTT_MinimaxPlayer>(FVector(), FRotator());

	// AI player = 1
	Players.Add(AI);

	b_turnHumanPlayer = true;
	ChessBoard->UpdateAllMoveBYColor(ETileOwner::WHITE);
	ChessBoard->UpdateAllMoveBYColor(ETileOwner::BLACK);
	Players[0]->OnTurn();
}

void AChessGameMode::CheckOnCheck(IChess_PlayerInterface* P)
{
	if (P->Color == EColor::WHITE)
	{
		P->b_OnCheck = ChessBoard->CheckOnCheck(ETileOwner::WHITE);
	}
	else
	{
		P->b_OnCheck = ChessBoard->CheckOnCheck(ETileOwner::BLACK);
	}
}

void AChessGameMode::CheckOnCkeckmate(IChess_PlayerInterface* P)
{
	P->b_OnCheckmate = P->b_OnCheck && P->b_OnStalemate;
}

void AChessGameMode::CheckOnStalemate(IChess_PlayerInterface* P)
{
	if (P->Color == EColor::WHITE)
	{
		P->b_OnStalemate = ChessBoard->CheckOnStalemate(ETileOwner::WHITE);
	}

	else
	{
		P->b_OnStalemate = ChessBoard->CheckOnStalemate(ETileOwner::BLACK);
	}
}

void AChessGameMode::HandlePawnPromotion(EPieceColor Color,EPieceName Name,bool bInGame)
{
	APiece* OldPiece = nullptr;
	FVector Location;
	FVector2D GridPosition;
	ATile* Tile = nullptr;
	APiece* NewPiece = nullptr;
	if (Color == EPieceColor::BLACK)
	{
		for (int32 i = 0; i < ChessBoard->GetGameField()->Size; i++)
		{
			Tile = ChessBoard->GetGameField()->GetTileBYXYPosition(0, i);
			if (Tile->GetOnPiece() != nullptr && Tile->GetOnPiece()->GetName() == EPieceName::PAWN)
			{
				OldPiece = Tile->GetOnPiece();
				break;
			}
				
		}

		if (OldPiece == nullptr) return;

		ChessBoard->GetBlackPieces().Remove(OldPiece);
		GridPosition = OldPiece->GetGridPosition();
		Location = OldPiece->GetActorLocation();
		OldPiece->Destroy();
		switch (Name)
		{
		case EPieceName::ROOK:
				NewPiece = GetWorld()->SpawnActor<ABlackRook>(ChessBoard->BlackRookClass, Location, FRotator::ZeroRotator);
				break;
			case EPieceName::KNIGHT:
				NewPiece = GetWorld()->SpawnActor<ABlackKnight>(ChessBoard->BlackKnightClass, Location, FRotator::ZeroRotator);
				break;
			case EPieceName::BISHOP:
				NewPiece = GetWorld()->SpawnActor<ABlackBishop>(ChessBoard->BlackBishopClass, Location, FRotator::ZeroRotator);
				break;
			case EPieceName::QUEEN:
				NewPiece = GetWorld()->SpawnActor<ABlackQueen>(ChessBoard->BlackQueenClass, Location, FRotator::ZeroRotator);
				break;
			default:
				NewPiece = GetWorld()->SpawnActor<ABlackPawn>(ChessBoard->BlackPawnClass, Location, FRotator::ZeroRotator);
				break;
		}
		if (Tile!= nullptr && NewPiece != nullptr)
		{
			Tile->SetOnPiece(NewPiece);
			NewPiece->SetGridPosition(GridPosition.X, GridPosition.Y);
			ChessBoard->GetBlackPieces().Add(NewPiece);
		}			
	}
	else
	{
		for (int32 i = 0; i < ChessBoard->GetGameField()->Size; i++)
		{
			Tile = ChessBoard->GetGameField()->GetTileBYXYPosition(ChessBoard->GetGameField()->Size-1, i);
			if (Tile->GetOnPiece() != nullptr && Tile->GetOnPiece()->GetName() == EPieceName::PAWN)
			{
				OldPiece = Tile->GetOnPiece();
				break;
			}
		}

		if (OldPiece == nullptr) return;

		ChessBoard->GetWhitePieces().Remove(OldPiece);
		GridPosition = OldPiece->GetGridPosition();
		Location = OldPiece->GetActorLocation();
		OldPiece->Destroy();
		switch (Name)
		{
		case EPieceName::ROOK:
			NewPiece = GetWorld()->SpawnActor<AWhiteRook>(ChessBoard->WhiteRookClass, Location, FRotator::ZeroRotator);
			break;
		case EPieceName::KNIGHT:
			NewPiece = GetWorld()->SpawnActor<AWhiteKnight>(ChessBoard->WhiteKnightClass, Location, FRotator::ZeroRotator);
			break;
		case EPieceName::BISHOP:
			NewPiece = GetWorld()->SpawnActor<AWhiteBishop>(ChessBoard->WhiteBishopClass, Location, FRotator::ZeroRotator);
			break;
		case EPieceName::QUEEN:
			NewPiece = GetWorld()->SpawnActor<AWhiteQueen>(ChessBoard->WhiteQueenClass, Location, FRotator::ZeroRotator);
			break;
		default:
			NewPiece = GetWorld()->SpawnActor<AWhiteQueen>(ChessBoard->WhiteQueenClass, Location, FRotator::ZeroRotator);
			break;
		}

		if (Tile != nullptr && NewPiece != nullptr) 
		{
			Tile->SetOnPiece(NewPiece);
			NewPiece->SetGridPosition(GridPosition.X, GridPosition.Y);
			ChessBoard->GetWhitePieces().Add(NewPiece);
		}
	}

	AChess_HumanPlayer* HumanPlayer = Cast<AChess_HumanPlayer>(Players[0]);
	if (bInGame)
	{
		HumanPlayer->ChessHUD->GetTopHistoryButtons()->SetTextOnButton(HumanPlayer->ChessHUD->GetTopHistoryButtons()->GetTextOnButton() + NewPiece->ToString());
		ChessBoard->GetTopMove().PawnPromotedTo = Name;
		TurnNextPlayer();
	}
		
	
}

void AChessGameMode::ResetGame()
{
	AChess_HumanPlayer* HumanPlayer = Cast<AChess_HumanPlayer>(*TActorIterator<AChess_HumanPlayer>(GetWorld()));
	if (HumanPlayer->IsMyTurn == true)
	{
		AChess_PlayerController* PC = Cast<AChess_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		PC->ChessHUD->ResetHistoryScrollBox();
		ChessBoard->ResetChessBoard();
		StartGame(Difficulty);
	}
	
}

void AChessGameMode::HandleReplay(int32 MoveIndex)
{
	AChess_HumanPlayer* HumanPlayer = Cast<AChess_HumanPlayer>(*TActorIterator<AChess_HumanPlayer>(GetWorld()));
	ChessBoard->UnShowSelectableTiles(HumanPlayer->Piece_SelectableMoves);
	if (HumanPlayer->IsMyTurn == true || bIsInReplay) 
	{
		bIsInReplay = true;
		HumanPlayer->IsMyTurn = false;
		if (MoveIndex > CurrentReplayMoveIndex-1)
		{
			ChessBoard->RestoreChessboardToMoveForward(CurrentReplayMoveIndex, MoveIndex);
		}
		else if (MoveIndex < CurrentReplayMoveIndex-1)
		{
			ChessBoard->RestoreChessboardToMoveBackward(CurrentReplayMoveIndex - 1, MoveIndex);
		}
		else if (CurrentReplayMoveIndex - 1 == MoveIndex) 
		{
			ChessBoard->RemoveMovesFromStartingIndex(MoveIndex);
			AChess_PlayerController* PC = Cast<AChess_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			PC->ChessHUD->RemoveButtonsFromTheHystoryScrollBox(MoveIndex);
			bIsInReplay = false;
			if (ChessBoard->GetTopMove().Player == EColor::WHITE)
			{
				b_turnHumanPlayer = true; //i want to use the TurnNextPlayer in order to update all the avaible moves, so i here i put true and with turn next player will be set to true
			}	
			else
			{
				b_turnHumanPlayer = false;
			}
			TurnNextPlayer();
		}
		CurrentReplayMoveIndex = MoveIndex+1;
	}
}
