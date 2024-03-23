// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveHistoryButton.h"
#include "Components/EditableTextBox.h"

void UMoveHistoryButton::SetMoveNumber(int32 Num)
{
	MoveNumber = Num;
}

int32 UMoveHistoryButton::GetMoveNumber()
{
	return MoveNumber;
}


void UMoveHistoryButton::SetTextOnButton(FString String)
{
	Text->SetText(FText::FromString(String));
}

FString UMoveHistoryButton::GetTextOnButton()
{
	return Text->GetText().ToString();
}


UWhiteMoveHistoryButton::UWhiteMoveHistoryButton() : UMoveHistoryButton()
{
	ColorOfPlayerInTurn = EColor::WHITE;
}

UBlackMoveHistoryButton::UBlackMoveHistoryButton() : UMoveHistoryButton()
{
	ColorOfPlayerInTurn = EColor::BLACK;
}
