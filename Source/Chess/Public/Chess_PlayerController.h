// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreSharedPCH.h"
#include "ChessHUD.h"
#include "PawnPromotionHUD.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Chess_HumanPlayer.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Chess_PlayerController.generated.h"

/**
 * Class to implement the player controller
*/
UCLASS()
class CHESS_API AChess_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	// Set the default value for this controller
	AChess_PlayerController();

	//Reference to a context
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* ChessContext;

	//Reference to a input action
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ClickAction;

	//Function to get the click on the grid
	void ClickOnGrid();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UChessHUD> ChessHUDClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPawnPromotionHUD> PawnPromotionHUDClass;

	UPROPERTY()
	UChessHUD* ChessHUD;

	UPROPERTY()
	UPawnPromotionHUD* PawnPromotionHUD;

protected:
	//Function called when starting game
	virtual void BeginPlay() override;
	//Function to setup the input component
	virtual void SetupInputComponent() override;
};