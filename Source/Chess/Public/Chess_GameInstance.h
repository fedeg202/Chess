// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Chess_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChess_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	//score of the human player
	UPROPERTY(EditAnywhere)
	int32 ScoreHumanPlayer = 0;
	//score of the ai player
	UPROPERTY(EditAnywhere)
	int32 ScoreAiPlayer = 0;
	//function to increment the score of the human player
	void IncrementScoreHumanPlayer();
	//Function to increment the score of the AI player
	void IncrementScoreAIPlayer();
	//return the wins of the human player
	UFUNCTION(BlueprintCallable)
	int32 GetScoreHumanPlayer();
	//Return the wins of the ai player
	UFUNCTION(BlueprintCallable)
	int32 GetScoreAIPlayer();

	// message to show every turn
	UPROPERTY(EditAnywhere)
	FString CurrentTurnMessage = "Current Player";

	// get the current turn message
	UFUNCTION(BlueprintCallable)
	FString GetTurnMessage();

	// set the turn message
	UFUNCTION(BlueprintCallable)
	void SetTurnMessage(FString Message);
};
