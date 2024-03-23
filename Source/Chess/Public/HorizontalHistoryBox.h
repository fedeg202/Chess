// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HorizontalHistoryBox.generated.h"


/**
 * 
 */
UCLASS()
class CHESS_API UHorizontalHistoryBox : public UUserWidget
{
	GENERATED_BODY()
public:
	//Method to set the number of the move in the text box in the Horizontal box
	void SetNumber(int32 Num);

	//Reference to the HorizontalBox
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UHorizontalBox* Box;

	//Methot to set text in the text box in the Horizontal box
	void SetText(FString String);

protected:
	//Reference to the text box in the horizontal box
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Text;
};
