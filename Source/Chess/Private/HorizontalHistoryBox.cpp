// Fill out your copyright notice in the Description page of Project Settings.


#include "HorizontalHistoryBox.h"

/**
 * @brief Method to set the number of the move in the HorizontalBox text box
 *
 * @param Num the number to be setted
 */
void UHorizontalHistoryBox::SetNumber(int32 Num)
{
	Text->SetText(FText::FromString(FString::FromInt(Num)+"."));
}

/**
 * @brief Method to set the text in the HorizontalBox text box
 *
 * @param String the string to be setted
 */
void UHorizontalHistoryBox::SetText(FString String)
{
	Text->SetText(FText::FromString(String));
}
