// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessBoard.h"
#include "Chess_PlayerInterface.h"
#include "Chess_HumanPlayer.h"
#include "StartMenu.h"
#include "EndGameWidget.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChessGameMode.generated.h"

/**
 * @brief Class to implement the ChessGame mode that inherit from the AGameModeBase
 */
UCLASS()
class CHESS_API AChessGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	//Set the default value for this actor
	AChessGameMode();

	// array of player interfaces
	TArray<IChess_PlayerInterface*> Players;
	bool b_turnHumanPlayer;
	//Reference to the class of the chessboard
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AChessBoard> ChessBoardClass;
	//Reference to the class of the starting menu
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStartMenu>	StartMenuClass;
	//Reference to the class of the end game widget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEndGameWidget>	EndGameWidgetClass;

	// reference to a ChessBoard object
	UPROPERTY(VisibleAnywhere)
	AChessBoard* ChessBoard;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// called at the end of the game turn
	void TurnNextPlayer();
	// called at the start of the game
	UFUNCTION(BlueprintCallable)
	void StartGame(int32 Diff);
	//Value that rapresent the chosen difficulty
	int32 Difficulty = 0;

	//Called to update booleans OnCheck value of the player interface at the and of every turn
	void CheckOnCheck(IChess_PlayerInterface* Player);
	//Called to update booleans OnCheckmate value of the player interface at the and of every turn
	void CheckOnCkeckmate(IChess_PlayerInterface* Player);
	//Called to update booleans OnStalemate value of the player interface at the and of every turn
	void CheckOnStalemate(IChess_PlayerInterface* Player);

	//called to handle the "Special rule" pawn promotion
	UFUNCTION(BlueprintCallable)
	void HandlePawnPromotion(EPieceColor Color, EPieceName Name,bool bIngame = true);
	
	//called to reset the game after the reset button pressed
	UFUNCTION(BlueprintCallable)
	void ResetGame();

	//Number of the current move displayed
	int32 CurrentReplayMoveIndex = 0;

	//Method to handle the replay functionality, takes the desired move index as a parameter
	UFUNCTION(BlueprintCallable)
	void HandleReplay(int32 MoveIndex);

	//Boolean value to handle replay functionality
	bool bIsInReplay = false;
	//Booelean value to handle the end of the game
	bool b_IsGameOver = false;

	//Function to check if there has been three times same state thus making the game a draw
	bool CheckFor3StateRepetitionDraw();

	//Blueprint callable function to change the human player camera from the chessHud
	UFUNCTION(BlueprintCallable)
	void ChangeCameraPosition();

	//Blueprint callable function to return to the starting menu where you can change the difficulty of the game
	UFUNCTION(BlueprintCallable)
	void ChangeDifficulty();

	//Reference to the backgorund music
	UPROPERTY(EditAnywhere)
	USoundBase* BackGroundMusic;

	//Reference to the sound component that play the background music
	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* MusicComponent;

};
