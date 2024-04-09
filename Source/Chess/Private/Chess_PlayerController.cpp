// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_PlayerController.h"
#include "Components/InputComponent.h"

/**
 * @brief AChess_PlayerController class constructor
 *
 */
AChess_PlayerController::AChess_PlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

/**
 * @brief Method to show the hud at the start of the game (Bleuprint callable)
 *
 */
void AChess_PlayerController::ShowHUD()
{
	if (ChessHUD->IsValidLowLevel())
		ChessHUD->AddToPlayerScreen();
}

/**
 * @brief Method to manage the widgets in case of stalemate
 *
 */
void AChess_PlayerController::OnStalemate()
{
	ChessHUD->OnStalemate();
	ChessHUD->RemoveFromParent();

	EndGameWidget->AddToPlayerScreen();
	EndGameWidget->MessageText->SetText(FText::FromString("Almost!"));
	EndGameWidget->ResultText->SetText(FText::FromString(Cast<UChess_GameInstance>(GetGameInstance())->GetTurnMessage()));
	EndGameWidget->PointText->SetText(FText::FromString("1/2-1/2"));
}

/**
 * @brief Method to manage the widgets in case of chekmate
 * 
 * @param Color EColor of the player in checkmate
 * @param bHumanWin boolean value to keep track if the winner is the human player
 *
 */
void AChess_PlayerController::OnCheckmate(EColor Color,bool bHumanWin)
{
	ChessHUD->OnCheckmate(Color);
	ChessHUD->RemoveFromParent();

	EndGameWidget->AddToPlayerScreen();

	if (bHumanWin)
	{
		EndGameWidget->MessageText->SetText(FText::FromString("Congratulations!"));
		EndGameWidget->ResultText->SetText(FText::FromString("You won!"));
	}
	else
	{
		EndGameWidget->MessageText->SetText(FText::FromString("Our greatest glory is not in never falling, but in rising every time we fall"));
		EndGameWidget->ResultText->SetText(FText::FromString("You lost!"));
	}

	if (Color == EColor::WHITE)
	{
		EndGameWidget->PointText->SetText(FText::FromString("0-1"));
	}
	else
	{
		EndGameWidget->PointText->SetText(FText::FromString("1-0"));
	}

}

/**
 * @brief Called when starting the game or when spawned
 *
 */
void AChess_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(ChessContext, 0);
	}
}

/**
 * @brief Method Setup the input component
 *
 */
void AChess_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &AChess_PlayerController::ClickOnGrid);
	}
}

/**
 * @brief Method to manage the HumanPlayer click
 *
 */
void AChess_PlayerController::ClickOnGrid()
{
	const auto HumanPlayer = Cast<AChess_HumanPlayer>(GetPawn());
	if (IsValid(HumanPlayer))
	{
		HumanPlayer->OnClick();
	}
}
