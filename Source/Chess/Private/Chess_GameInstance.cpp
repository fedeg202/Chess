// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_GameInstance.h"

/**
 * @brief Getter method to the turn Message
 *
 * @return FString with the current turn message
 */
FString UChess_GameInstance::GetTurnMessage()
{
	return CurrentTurnMessage;
}

/**
 * @brief Setter method of the turn message
 * 
 * @param Message FString of the message to be set
 */
void UChess_GameInstance::SetTurnMessage(FString Message)
{
	CurrentTurnMessage = Message;
}
