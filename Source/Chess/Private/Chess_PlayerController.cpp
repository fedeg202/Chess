// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_PlayerController.h"
#include "Components/InputComponent.h"

AChess_PlayerController::AChess_PlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void AChess_PlayerController::ShowHUD()
{
	if (ChessHUD->IsValidLowLevel())
		ChessHUD->AddToPlayerScreen();
}

void AChess_PlayerController::OnStalemate()
{
	ChessHUD->OnStalemate();
	ChessHUD->RemoveFromParent();

	EndGameWidget->AddToPlayerScreen();
	EndGameWidget->MessageText->SetText(FText::FromString("Almost!"));
	EndGameWidget->PointText->SetText(FText::FromString("1/2-1/2"));
}

void AChess_PlayerController::OnCheckmate(EColor Color,bool bHumanWin)
{
	ChessHUD->OnCheckmate(Color);
	ChessHUD->RemoveFromParent();

	EndGameWidget->AddToPlayerScreen();

	if (bHumanWin)
	{
		EndGameWidget->MessageText->SetText(FText::FromString("Congratulations!"));
	}
	else
	{
		EndGameWidget->MessageText->SetText(FText::FromString("Our greatest glory is not in never falling, but in rising every time we fall"));
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

void AChess_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(ChessContext, 0);
	}
}

void AChess_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &AChess_PlayerController::ClickOnGrid);
	}
}

void AChess_PlayerController::ClickOnGrid()
{
	const auto HumanPlayer = Cast<AChess_HumanPlayer>(GetPawn());
	if (IsValid(HumanPlayer))
	{
		HumanPlayer->OnClick();
	}
}
