// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveHistoryButton.h"
#include "Components/EditableTextBox.h"

/**
 * @brief UMoveHistoryButton class constructor
 *
 */
void UMoveHistoryButton::SetMoveNumber(int32 Num)
{
	MoveNumber = Num;
}

/**
 * @brief Getter for the attribute MoveNumber
 *
 */
int32 UMoveHistoryButton::GetMoveNumber()
{
	return MoveNumber;
}


/**
 * @brief Method to set the text on the button
 * 
 * @param String the string you want to put on the button
 */
void UMoveHistoryButton::SetTextOnButton(FString String)
{
	Text->SetText(FText::FromString(String));
}

/**
 * @brief Getter for the text on the button
 * 
 * @return The text that is on the button as a FString
 */
FString UMoveHistoryButton::GetTextOnButton()
{
	return Text->GetText().ToString();
}

/**
 * @brief UWhiteMoveHistoryButton class constructor
 *
 */
UWhiteMoveHistoryButton::UWhiteMoveHistoryButton() : UMoveHistoryButton()
{
	ColorOfPlayerInTurn = EColor::WHITE;
}

/**
 * @brief UBlackMoveHistoryButton class constructor
 *
 */
UBlackMoveHistoryButton::UBlackMoveHistoryButton() : UMoveHistoryButton()
{
	ColorOfPlayerInTurn = EColor::BLACK;
}
