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

	// Human player = 0
	Players.Add(HumanPlayer);
	// Random Player
	auto* AI = GetWorld()->SpawnActor<AChess_RandomPlayer>(FVector(), FRotator());
	AI->ChessBoard = ChessBoard;
	// MiniMax Player
	//auto* AI = GetWorld()->SpawnActor<ATTT_MinimaxPlayer>(FVector(), FRotator());

	// AI player = 1
	Players.Add(AI);

	StartGame();
}

void AChessGameMode::TurnNextPlayer()
{
	Player = !Player;
	
	if (Player) 
	{
		Players[0]->OnTurn();
	}
	else
	{
		Players[1]->OnTurn();
	}
}

void AChessGameMode::StartGame()
{
	Player = true;
	Players[0]->OnTurn();
}
