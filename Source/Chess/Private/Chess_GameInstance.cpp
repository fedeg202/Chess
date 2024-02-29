// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_GameInstance.h"

FString UChess_GameInstance::GetTurnMessage()
{
	return CurrentTurnMessage;
}

void UChess_GameInstance::SetTurnMessage(FString Message)
{
	CurrentTurnMessage = Message;
}
