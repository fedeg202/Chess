// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MoveHistoryButton.h"
#include "HorizontalHistoryBox.h"
#include "Chess_PlayerInterface.h"


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChessHUD.generated.h"


/**
 * @brief Class to implement the main HUD displayed during game, inherit from UUserWidget
 */
UCLASS()
class CHESS_API UChessHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	//reference to the class of the WhiteMoveHistoryButton
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWhiteMoveHistoryButton> WhiteMoveHistoryButtonClass;
	//reference to the class of the BlackMoveHistoryButton
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBlackMoveHistoryButton> BlackMoveHistoryButtonClass;
	//reference to the class of the HorizontalBox
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHorizontalHistoryBox> HorizontalBoxClass;

	//Method to add a button to the scroll box displaying all the moves
	UFUNCTION()
	void AddMoveButtonToTheHistoryScrollBox(FString MoveCode, EColor Color);

	//Method to reset the scroll box displaying all the moves
	void ResetHistoryScrollBox();

	//Methot to remove all the buttons from the scroll box displaying all the moves, that have an index bigger tha the starting index passed as a parameter
	void RemoveButtonsFromTheHystoryScrollBox(int32 StartingIndex);

	//Method to obtain the top history button in the scroll box displaying all the moves
	UMoveHistoryButton* GetTopHistoryButtons();

	//Method to obtain the top horizontal box in the scroll box displaying all the moves
	UHorizontalHistoryBox* GetTopHorizontalHistoryBoxes();

	//Method to show in the moves of the HUD that a player has checked the other
	void OnCheck();

	//Method to show in the moves of the HUD that a player has checkmated the other
	void OnCheckmate(EColor PlayerColor);

	//Method to show a draw on the HUD
	void OnStalemate();

protected:
	//Reference to the array containing all the Buttons with the moves
	TArray<UMoveHistoryButton*> HistoryButtons;
	//Reference to the array containing all the horizontal boxes of the scroll box
	TArray<UHorizontalHistoryBox*> HorizontalHistoryBoxes;

	//Reference to the scroll box
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UScrollBox* MoveHistoryScrollBox;
};
