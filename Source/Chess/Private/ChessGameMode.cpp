// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameMode.h"

#include "Engine.h"

#include "Chess_PlayerController.h"
#include "Chess_HumanPlayer.h"
#include "Chess_RandomPlayer.h"
//#include "TTT_MinimaxPlayer.h"

AChessGameMode::AChessGameMode()
{
	//PlayerControllerClass = AChess_PlayerController::StaticClass();
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

	float CameraPosX = ((ChessBoard->GetGameField()->TileSize * ChessBoard->GetGameField()->Size)/2);
	FVector CameraPos(CameraPosX, CameraPosX, 1000.0f);
	HumanPlayer->SetActorLocationAndRotation(CameraPos, FRotationMatrix::MakeFromX(FVector(0, 0, -1)).Rotator());

	HumanPlayer->ChessBoard = ChessBoard;
	HumanPlayer->Color = EColor::WHITE;

	// Human player = 0
	Players.Add(HumanPlayer);
	// Random Player
	auto* AI = GetWorld()->SpawnActor<AChess_RandomPlayer>(FVector(), FRotator());
	AI->ChessBoard = ChessBoard;
	AI->Color = EColor::BLACK;
	// MiniMax Player
	//auto* AI = GetWorld()->SpawnActor<ATTT_MinimaxPlayer>(FVector(), FRotator());

	// AI player = 1
	Players.Add(AI);

	StartGame();
}

void AChessGameMode::TurnNextPlayer()
{
	Player = !Player;
	ChessBoard->UpdateAllMoveBYColor(ETileOwner::WHITE);
	ChessBoard->UpdateAllMoveBYColor(ETileOwner::BLACK);

	if (Player) 
	{
		CheckOnCheck(Players[0]);
		CheckOnStalemate(Players[0]);
		CheckOnCkeckmate(Players[0]);
		if (Players[0]->B_OnCheckmate) Players[0]->OnLose();
		else if (Players[0]->B_OnStalemate) Players[0]->OnStalemate();
		else if (Players[0]->B_OnCheck) Players[0]->OnCheck();
		else Players[0]->OnTurn();
	}
	else
	{
		CheckOnCheck(Players[1]);
		CheckOnStalemate(Players[1]);
		CheckOnCkeckmate(Players[1]);
		if (Players[1]->B_OnCheckmate) Players[0]->OnWin();
		else if (Players[1]->B_OnStalemate) Players[1]->OnStalemate();
		else if (Players[1]->B_OnCheck) Players[1]->OnCheck();
		else Players[1]->OnTurn();
	}
}

void AChessGameMode::StartGame()
{
	Player = true;
	ChessBoard->UpdateAllMoveBYColor(ETileOwner::WHITE);
	ChessBoard->UpdateAllMoveBYColor(ETileOwner::BLACK);
	Players[0]->OnTurn();
}

void AChessGameMode::CheckOnCheck(IChess_PlayerInterface* P)
{
	if (P->Color == EColor::WHITE)
	{
		P->B_OnCheck = ChessBoard->CheckOnCheck(ETileOwner::WHITE);
	}
	else
	{
		P->B_OnCheck = ChessBoard->CheckOnCheck(ETileOwner::BLACK);
	}
}

void AChessGameMode::CheckOnCkeckmate(IChess_PlayerInterface* P)
{
	P->B_OnCheckmate = P->B_OnCheck && P->B_OnStalemate;
}

void AChessGameMode::CheckOnStalemate(IChess_PlayerInterface* P)
{
	if (P->Color == EColor::WHITE)
	{
		P->B_OnStalemate = ChessBoard->CheckOnStalemate(ETileOwner::WHITE);
	}

	else
	{
		P->B_OnStalemate = ChessBoard->CheckOnStalemate(ETileOwner::BLACK);
	}
}
