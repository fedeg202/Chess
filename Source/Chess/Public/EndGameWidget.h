// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TextBlock.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

/**
 * @brief Class to implement the widget at the end of the game
 */
UCLASS()
class CHESS_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//Reference to the text block that display a message at the end of the game
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* MessageText;

	//Reference to the text block that display the "point" at the end of the game
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* PointText;

	//reference to the text block that dusplay the "Result" of the game for the huma player (you won/you lose)
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ResultText;
	
};
