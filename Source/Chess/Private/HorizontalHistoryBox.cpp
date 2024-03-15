// Fill out your copyright notice in the Description page of Project Settings.


#include "HorizontalHistoryBox.h"

void UHorizontalHistoryBox::SetNumber(int32 Num)
{
	Text->SetText(FText::FromString(FString::FromInt(Num)+"."));
}
