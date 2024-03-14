// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Chess_PlayerInterface.h"
#include "Components/TextBlock.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoveHistoryButton.generated.h"


/**
 * Button to be shown in the Move History
 */
UCLASS()
class CHESS_API UMoveHistoryButton : public UUserWidget
{
	GENERATED_BODY()
public:
	
	void SetMoveNumber(int32 Num);
	int32 GetMoveNumber();

	virtual EColor GetPlayerInTurn();

	void SetTextOnButton(FString String);
	FString GetTextOnButton();

protected:
	int32 MoveNumber;
	EColor ColorOfPlayerInTurn;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Text;
};

UCLASS()
class CHESS_API UWhiteMoveHistoryButton : public UMoveHistoryButton
{
	GENERATED_BODY()
public:
	UWhiteMoveHistoryButton();

};

UCLASS()
class CHESS_API UBlackMoveHistoryButton : public UMoveHistoryButton
{
	GENERATED_BODY()
public:
	UBlackMoveHistoryButton();
};