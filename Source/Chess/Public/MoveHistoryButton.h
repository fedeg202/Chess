// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Chess_PlayerInterface.h"
#include "Components/TextBlock.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoveHistoryButton.generated.h"


/**
 * @brief Class to implement the Button to be shown in the Move History
 */
UCLASS()
class CHESS_API UMoveHistoryButton : public UUserWidget
{
	GENERATED_BODY()
public:
	//Method to set the MoveNumber attribute
	void SetMoveNumber(int32 Num);

	//Method to obtain the value of MoveNumber attribute
	UFUNCTION(BlueprintCallable)
	int32 GetMoveNumber();
	
	//Method to set the text on the button
	void SetTextOnButton(FString String);
	//Method to obatin the text on the button
	FString GetTextOnButton();

protected:
	//MoveNumber attribute to keep track of the move number of the button
	int32 MoveNumber;
	//Attribute to keep track of the color of the plyeer that made the move
	EColor ColorOfPlayerInTurn;

	//Reference to the text blox inside of the button
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Text;
};

/**
 * @brief Class to implement the Button to be shown in the Move History for the White Moves, that inherit from the UMoveHistoryButton class
 */
UCLASS()
class CHESS_API UWhiteMoveHistoryButton : public UMoveHistoryButton
{
	GENERATED_BODY()
public:
	UWhiteMoveHistoryButton();

};

/**
 * @brief Class to implement the Button to be shown in the Move History for the Black Moves, that inherit from the UMoveHistoryButton class
 */
UCLASS()
class CHESS_API UBlackMoveHistoryButton : public UMoveHistoryButton
{
	GENERATED_BODY()
public:
	UBlackMoveHistoryButton();
};