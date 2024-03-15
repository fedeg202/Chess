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
	void SetNumber(int32 Num);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UHorizontalBox* Box;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Text;
};
