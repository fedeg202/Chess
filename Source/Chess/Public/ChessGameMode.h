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
	// called at the start of the game
	void StartGame();

	//Called to update booleans OnCheck value of the player interface at the and of every turn
	void CheckOnCheck(IChess_PlayerInterface* Player);
	//Called to update booleans OnCheckmate value of the player interface at the and of every turn
	void CheckOnCkeckmate(IChess_PlayerInterface* Player);
	//Called to update booleans OnStalemate value of the player interface at the and of every turn
	void CheckOnStalemate(IChess_PlayerInterface* Player);

	//called to handle the "Special rule" pawn promotion
	UFUNCTION(BlueprintCallable)
	void HandlePawnPromotion(EPieceColor Color, EPieceName Name);
	
	//called to reset the game after the reset button pressed
	UFUNCTION(BlueprintCallable)
	void ResetGame();
};
