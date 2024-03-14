// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessHUD.h"
#include "Components/ScrollBox.h"
#include "Chess_PlayerController.h"

void UChessHUD::AddMoveButtonToTheHistoryScrollBox(FString MoveCode, EColor Color)
{
    UMoveHistoryButton* MoveButton;
    if (Color == EColor::BLACK)
        MoveButton = CreateWidget<UBlackMoveHistoryButton>(this, BlackMoveHistoryButtonClass);
    else
        MoveButton = CreateWidget<UWhiteMoveHistoryButton>(this, WhiteMoveHistoryButtonClass);

    if (MoveButton != nullptr)
    {
        MoveButton->SetMoveNumber(HistoryButtons.Num());
        MoveButton->SetTextOnButton(MoveCode);
        HistoryButtons.Add(MoveButton);
        MoveHistoryScrollBox->AddChild(MoveButton);
    }
    else
    {
        // Handle error: Unable to create move button
        UE_LOG(LogTemp, Warning, TEXT("Failed to create move button for move: %s"), *MoveCode);
    }
}

void UChessHUD::ResetHistoryScrollBox()
{
	for (int32 i = 0; i < HistoryButtons.Num(); i++)
	{
		MoveHistoryScrollBox->RemoveChild(HistoryButtons[i]);
	}
	HistoryButtons.Empty();
}

UMoveHistoryButton* UChessHUD::GetTopHistoryButtons()
{
	return HistoryButtons.Top();
}
