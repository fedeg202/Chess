// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Chess_GameInstance.h"
#include "ChessBoard.h"
#include "Chess_PlayerInterface.h"
#include "Kismet/GameplayStatics.h"
#include "ChessHUD.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Chess_MinimaxPlayer.generated.h"

/*
* Class to implement the Minimax player, inherit from Pawn and Chess_PlayerInterface
*/

UCLASS()
class CHESS_API AChess_MinimaxPlayer : public APawn, public IChess_PlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AChess_MinimaxPlayer();

	//Reference to a game instance object
	UChess_GameInstance* GameInstance;

	//Reference to a chessboard object
	AChessBoard* ChessBoard;

	//Reference to the HUD
	UPROPERTY()
	UChessHUD* ChessHUD;

	//Reference to an array of sounds to play
	TArray<USoundBase*> SoundsToPlay;
	//Reference to the audio component to play sounds during the game
	UAudioComponent* AudioComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Bool value to manage the turn of this player
	bool IsMyTurn = false;
	//Max value of the chessboard evalutor
	int32 MaxValue = 10000;
	//Minimax algorithm depth
	int32 MiniMaxDepth = 4;
	//Reference to the turn selected piece
	APiece* SelectedPiece;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Override of OnTurn Chess_PlayerInterface method to start the player turn and show a custom message for this player
	virtual void OnTurn() override;
	//Override of OnWin Chess_PlayerInterface method to show a custom message for this player win
	virtual void OnWin() override;
	//Override of OnLose Chess_PlayerInterface method to show a custom message for this player lose
	virtual void OnLose() override;

	//Override of OnCheck Chess_PlayerInterface method to show a custom message for when this player when is in check
	virtual void OnCheck() override;
	//Override of OnStalemate Chess_PlayerInterface method to show a custom message for this player when is in stalemate
	virtual void OnStalemate() override;
	//Override of OnCheckmate Chess_PlayerInterface method to show a custom message for this player when is in checkmate
	virtual void OnCheckmate() override;

	//Method to evaluate the board
	int32 EvaluateBoard();
	//AlphaBeta pruning MIniMax algorithm
	int32 AlfaBetaMiniMax(int32 Depth, int32 alpha, int32 beta, bool IsMax);
	//Method to find the best move using the minimax algorithm
	FCoupleTile FindBestMove();
	//Method to play sounds during game
	void PlaySound(int32 SoundIndex);
};

