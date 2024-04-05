// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Chess_GameInstance.h"
#include "ChessBoard.h"
#include "Chess_PlayerInterface.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ChessHUD.h"
#include "PawnPromotionHUD.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Chess_HumanPlayer.generated.h"


UCLASS()
class CHESS_API AChess_HumanPlayer : public APawn, public IChess_PlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AChess_HumanPlayer();
	//Reference to a camera component
	UCameraComponent* Camera;
	//Reference to the GameInstance
	UChess_GameInstance* GameInstance;

	//Reference to the HUD
	UPROPERTY()
	UChessHUD* ChessHUD;

	//Reference to the PawnPromotion widget
	UPROPERTY()
	UPawnPromotionHUD* PawnPromotionHUD;

	// reference to a ChessBoard object
	UPROPERTY(VisibleAnywhere)
	AChessBoard* ChessBoard;

	//Array of tile that are selectable by the selected piece
	TArray<ATile*> Piece_SelectableMoves;

	//Boolen value to manage the turn
	bool IsMyTurn = false;

	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> SoundsToPlay;

	UAudioComponent* AudioComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Reference to the selected piece of the turn
	APiece* SelectedPiece;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Overrride of the PlayerInterface method called when the player is in turn
	virtual void OnTurn() override;
	//Overrride of the PlayerInterface method called when the player win
	virtual void OnWin() override;
	//Overrride of the PlayerInterface method called when the player lose
	virtual void OnLose() override;

	//Overrride of the PlayerInterface method called when the player is in on Check
	virtual void OnCheck() override;
	//Overrride of the PlayerInterface method called when the player is in Stalemate
	virtual void OnStalemate() override;
	//Overrride of the PlayerInterface method called when the player is in Checkmate
	virtual void OnCheckmate() override;

	//Methot to handle the player click
	UFUNCTION()
	void OnClick();

	void PlaySound(int32 SoundIndex);

};
