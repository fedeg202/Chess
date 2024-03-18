// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MoveHistoryButton.h"
#include "HorizontalHistoryBox.h"
#include "Chess_PlayerInterface.h"


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChessHUD.generated.h"


/**
 * Class to implement the main HUD displayed during game
 */
UCLASS()
class CHESS_API UChessHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWhiteMoveHistoryButton> WhiteMoveHistoryButtonClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBlackMoveHistoryButton> BlackMoveHistoryButtonClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHorizontalHistoryBox> HorizontalBoxClass;

	UFUNCTION()
	void AddMoveButtonToTheHistoryScrollBox(FString MoveCode, EColor Color);

	void ResetHistoryScrollBox();

	void RemoveButtonsFromTheHystoryScrollBox(int32 StartingIndex);

	UMoveHistoryButton* GetTopHistoryButtons();

	UHorizontalHistoryBox* GetTopHorizontalHistoryBoxes();

protected:
	TArray<UMoveHistoryButton*> HistoryButtons;
	TArray<UHorizontalHistoryBox*> HorizontalHistoryBoxes;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UScrollBox* MoveHistoryScrollBox;
};
