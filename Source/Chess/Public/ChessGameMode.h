// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessBoard.h"
#include "Chess_PlayerInterface.h"
#include "Chess_HumanPlayer.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChessGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AChessGameMode();

	bool IsGameOver;
	// array of player interfaces
	TArray<IChess_PlayerInterface*> Players;
	bool Player;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AChessBoard> ChessBoardClass;

	// reference to a ChessBoard object
	UPROPERTY(VisibleAnywhere)
	AChessBoard* ChessBoard;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// called at the end of the game turn
	void TurnNextPlayer();

	void StartGame();
	//void MovePiece();
};
