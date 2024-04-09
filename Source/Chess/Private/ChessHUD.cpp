// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessHUD.h"
#include "Components/ScrollBox.h"
#include "Chess_PlayerController.h"


/*
* @brief Method to add a button to the history scroll box, if is a black move you simply add it to the last horizontal box,
*        if is white move create a new horizontal box and put the button in the horizontal box
*
* @param MoveCode the string that has to be putted in the buttonù
* @param Color the color the player that made the move
*/
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

/*
* @brief Method to reset the history scroll box to its starting state
*
*/
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

/*
* @brief Method to remove all the buttons from the history scroll box starting from the button that has the index that
*        is passed as a parameter
* 
* @param StartingIndex index from where starting to remove all the buttons that have a greater index
*/
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

/*
* @brief Method to obtain the top element of the HistoryButtons array
*
* @return reference to the top history button
*/
UMoveHistoryButton* UChessHUD::GetTopHistoryButtons()
{
	return HistoryButtons.Top();
}

/*
* @brief Method to obtain the top element of the HistoryBoxes array
*
* @return reference to the top history box
*/
UHorizontalHistoryBox* UChessHUD::GetTopHorizontalHistoryBoxes()
{
    return HorizontalHistoryBoxes.Top();
}

/*
* @brief Method to complete the algebraic notation of the history buttons in case of one of the player has been
*        putted in check
*
*/
void UChessHUD::OnCheck()
{
    UMoveHistoryButton* TopButton = HistoryButtons.Top();
    if (!TopButton->GetTextOnButton().Contains("+"))
        TopButton->SetTextOnButton(TopButton->GetTextOnButton() + "+");
}

/*
* @brief Method to complete the algebraic notation of the history buttons and the notation of the win in case of one of the player has been
*        putted in checkmate
*/
void UChessHUD::OnCheckmate(EColor PlayerColor)
{
    UMoveHistoryButton* TopButton = HistoryButtons.Top();
    TopButton->SetTextOnButton(TopButton->GetTextOnButton() + "#");
    UHorizontalHistoryBox* HorizontalBox = CreateWidget<UHorizontalHistoryBox>(this, HorizontalBoxClass);
    if (PlayerColor == EColor::WHITE)
        HorizontalBox->SetText("0-1");
    else
        HorizontalBox->SetText("1-0");
    MoveHistoryScrollBox->AddChild(HorizontalBox);
    HorizontalHistoryBoxes.Add(HorizontalBox);
}
/*
* @brief Method put the notation of the stalemate
*
*/
void UChessHUD::OnStalemate()
{
    UHorizontalHistoryBox* HorizontalBox = CreateWidget<UHorizontalHistoryBox>(this, HorizontalBoxClass);
    HorizontalBox->SetText("1/2-1/2");
    MoveHistoryScrollBox->AddChild(HorizontalBox);
    HorizontalHistoryBoxes.Add(HorizontalBox);
}
