// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessHUD.h"
#include "Components/ScrollBox.h"
#include "Chess_PlayerController.h"


void UChessHUD::AddMoveButtonToTheHistoryScrollBox(FString MoveCode, EColor Color)
{
    UMoveHistoryButton* MoveButton;
    UHorizontalHistoryBox* HorizontalBox;
    if (Color == EColor::BLACK)
    {
        HorizontalBox = GetTopHorizontalHistoryBoxes();
        MoveButton = CreateWidget<UBlackMoveHistoryButton>(this, BlackMoveHistoryButtonClass);
    }
    else 
    {
        HorizontalBox = CreateWidget<UHorizontalHistoryBox>(this, HorizontalBoxClass);
        MoveButton = CreateWidget<UWhiteMoveHistoryButton>(this, WhiteMoveHistoryButtonClass);
    }
        

    if (MoveButton != nullptr && HorizontalBox != nullptr)
    {
        MoveButton->SetMoveNumber(HistoryButtons.Num());
        MoveButton->SetTextOnButton(MoveCode);
        HistoryButtons.Add(MoveButton);
        HorizontalBox->Box->AddChild(MoveButton);

        if (Color == EColor::WHITE)
        {
            HorizontalBox->SetNumber(HorizontalHistoryBoxes.Num() + 1);
            HorizontalHistoryBoxes.Add(HorizontalBox);
            MoveHistoryScrollBox->AddChild(HorizontalBox);
        }      
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

    for (int32 i = 0; i < HorizontalHistoryBoxes.Num(); i++)
    {
        MoveHistoryScrollBox->RemoveChild(HorizontalHistoryBoxes[i]);
    }
    HorizontalHistoryBoxes.Empty();
}

void UChessHUD::RemoveButtonsFromTheHystoryScrollBox(int32 StartingIndex)
{
    int32 HorizontalBoxIndex = FMath::Floor(StartingIndex / 2);
    int32 i = HistoryButtons.Num()-1;
    for (; i > StartingIndex; i = HistoryButtons.Num()-1)
    {
        HistoryButtons[i]->RemoveFromParent();
        HistoryButtons.Pop(true);
    }

    int32 j = HorizontalHistoryBoxes.Num()-1;
    for (; j > HorizontalBoxIndex; j = HorizontalHistoryBoxes.Num()-1)
    {
        HorizontalHistoryBoxes[j]->RemoveFromParent();
        HorizontalHistoryBoxes.Pop(true);
    }
}

UMoveHistoryButton* UChessHUD::GetTopHistoryButtons()
{
	return HistoryButtons.Top();
}

UHorizontalHistoryBox* UChessHUD::GetTopHorizontalHistoryBoxes()
{
    return HorizontalHistoryBoxes.Top();
}
