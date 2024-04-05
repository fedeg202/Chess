// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameMode.h"

#include "Engine.h"

#include "Chess_PlayerController.h"
#include "Chess_HumanPlayer.h"
#include "Chess_RandomPlayer.h"
#include "Chess_MinimaxPlayer.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"

AChessGameMode::AChessGameMode()
{
	PlayerControllerClass = AChess_PlayerController::StaticClass();
	DefaultPawnClass = AChess_HumanPlayer::StaticClass();
}

void AChessGameMode::BeginPlay()
{

	Super::BeginPlay();

	b_IsGameOver = false;

	AChess_HumanPlayer* HumanPlayer = Cast<AChess_HumanPlayer>(*TActorIterator<AChess_HumanPlayer>(GetWorld()));

	if (ChessBoardClass != nullptr)
	{
		ChessBoard = GetWorld()->SpawnActor<AChessBoard>(ChessBoardClass);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Game Field is null"));
	}

	float CameraPosX = (ChessBoard->GetGameField()->TileSize * (ChessBoard->GetGameField()->Size-1))/2;
	FVector CameraPos(CameraPosX, CameraPosX, 1050.0f);
	HumanPlayer->SetActorLocationAndRotation(CameraPos, FRotationMatrix::MakeFromX(FVector(0, 0, -1)).Rotator());

	HumanPlayer->ChessBoard = ChessBoard;
	HumanPlayer->Color = EColor::WHITE;

	// Human player = 0
	Players.Add(HumanPlayer);
	
	AChess_PlayerController* PC = Cast<AChess_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainMenu = CreateWidget<UMainMenu>(PC, MainMenuClass);

	PC->EndGameWidget = CreateWidget<UEndGameWidget>(PC, EndGameWidgetClass);

	MainMenu->AddToPlayerScreen();
}

void AChessGameMode::TurnNextPlayer()
{
	AChess_PlayerController* PC = Cast<AChess_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (CheckFor3StateRepetitionDraw())
	{
		PC->OnStalemate();
		b_IsGameOver = true;
		Players[0]->OnStalemate();
	}
	else
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
			if (Players[0]->b_OnCheckmate)
			{
				b_IsGameOver = true;
				PC->OnCheckmate(Players[0]->Color,false);
				Players[0]->OnLose();
			}
			else if (Players[0]->b_OnStalemate)
			{
				PC->OnStalemate();
				b_IsGameOver = true;
				Players[0]->OnStalemate();
			}
			else if (Players[0]->b_OnCheck)
			{
				PC->ChessHUD->OnCheck();
				Players[0]->OnCheck();
			}
			else Players[0]->OnTurn();
		}
		else
		{
			CheckOnCheck(Players[1]);
			CheckOnStalemate(Players[1]);
			CheckOnCkeckmate(Players[1]);
			if (Players[1]->b_OnCheckmate)
			{
				b_IsGameOver = true;
				PC->OnCheckmate(Players[1]->Color,true);
				Players[0]->OnWin();
			}
			else if (Players[1]->b_OnStalemate)
			{
				PC->OnStalemate();
				b_IsGameOver = true;
				Players[1]->OnStalemate();
			}
			else if (Players[1]->b_OnCheck)
			{
				PC->ChessHUD->OnCheck();
				Players[1]->OnCheck();
			}
			else Players[1]->OnTurn();
		}
	}
}

void AChessGameMode::StartGame(int32 Diff)
{

	b_IsGameOver = false;

	if (Diff!=Difficulty)
		Difficulty = Diff;

	AChess_HumanPlayer* HumanPlayer = Cast<AChess_HumanPlayer>(*TActorIterator<AChess_HumanPlayer>(GetWorld()));
	
	if (Difficulty < 2)
	{
		//Random player
		auto* AI = GetWorld()->SpawnActor<AChess_RandomPlayer>(FVector(), FRotator());
		AI->ChessBoard = ChessBoard;
		AI->Color = EColor::BLACK;
		AI->SoundsToPlay = HumanPlayer->SoundsToPlay;
		Players.Add(AI);
	}
	else 
	{
		//Minimax player
		auto* AI = GetWorld()->SpawnActor<AChess_MinimaxPlayer>(FVector(), FRotator());
		AI->ChessBoard = ChessBoard;
		AI->Color = EColor::BLACK;
		AI->SoundsToPlay = HumanPlayer->SoundsToPlay;
		Players.Add(AI);
	}
	// AI player -> Players[1]

	

	CurrentReplayMoveIndex = 0;
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
	if (HumanPlayer->IsMyTurn == true || b_IsGameOver)
	{
		IChess_PlayerInterface* AIPlayer = Players.Pop(true);
		if (Difficulty < 2)
			Cast<AChess_RandomPlayer>(AIPlayer)->Destroy();
		else if (Difficulty >= 2)
			Cast<AChess_MinimaxPlayer>(AIPlayer)->Destroy();
	
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
	if (HumanPlayer->IsMyTurn == true || bIsInReplay || b_IsGameOver)
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
			if (!b_IsGameOver)
			{
				ChessBoard->StateOccurrences[ChessBoard->GetChessboardStateString()]--;
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
		}
		CurrentReplayMoveIndex = MoveIndex+1;
	}
}

bool AChessGameMode::CheckFor3StateRepetitionDraw()
{
	FString State = ChessBoard->GetChessboardStateString();

	if (ChessBoard->StateOccurrences.Contains(State))
	{
		ChessBoard->StateOccurrences[State]++;
		if (ChessBoard->StateOccurrences[State] == 3) return true;
	}
		
	else ChessBoard->StateOccurrences.Add(State,1);
	
	return false;
}

void AChessGameMode::ChangeCameraPosition()
{
	AChess_HumanPlayer* HumanPlayer = Cast<AChess_HumanPlayer>(*TActorIterator<AChess_HumanPlayer>(GetWorld()));
	HumanPlayer->ChangeCameraPosition();
}

void AChessGameMode::ChangeDifficulty()
{
	IChess_PlayerInterface* AIPlayer = Players.Pop(true);
	if (Difficulty<2)
		Cast<AChess_RandomPlayer>(AIPlayer)->Destroy();
	else if (Difficulty>=2)
		Cast<AChess_MinimaxPlayer>(AIPlayer)->Destroy();

	ChessBoard->ResetChessBoard();
	AChess_PlayerController* PC = Cast<AChess_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->ChessHUD->ResetHistoryScrollBox();
	
	MainMenu->AddToPlayerScreen();
}
