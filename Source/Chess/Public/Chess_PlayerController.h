// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreSharedPCH.h"
#include "ChessHUD.h"
#include "PawnPromotionHUD.h"
#include "EndGameWidget.h"
#include "StartMenu.h"

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

	//ChessHUD class
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UChessHUD> ChessHUDClass;

	//PawnPromotionHUD class
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPawnPromotionHUD> PawnPromotionHUDClass;

	//Reference to the HUD
	UPROPERTY()
	UChessHUD* ChessHUD;

	//Reference to the PawnPromotion widget
	UPROPERTY()
	UPawnPromotionHUD* PawnPromotionHUD;
	
	//Reference to the end game widget
	UPROPERTY()
	UEndGameWidget* EndGameWidget;

	//Reference to the start menu
	UPROPERTY()
	UStartMenu* StartMenu;

	//Function to show the HUD
	UFUNCTION(BlueprintCallable)
	void ShowHUD();

	//Method to correct display messages on the end game widget
	void OnStalemate();

	//Method to correct display messages on the end game widget
	void OnCheckmate(EColor Color,bool bHumanWin);

protected:
	//Function called when starting game
	virtual void BeginPlay() override;
	//Function to setup the input component
	virtual void SetupInputComponent() override;
};