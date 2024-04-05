// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TextBlock.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* MessageText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* PointText;

	bool bHumanWin;

	bool bStale;
	
};
