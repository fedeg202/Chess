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
 * 
*/
UCLASS()
class CHESS_API AChess_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AChess_PlayerController();

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* ChessContext;


	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ClickAction;

	void ClickOnGrid();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UChessHUD> ChessHUDClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPawnPromotionHUD> PawnPromotionHUDClass;


protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
};