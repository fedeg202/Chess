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

	UCameraComponent* Camera;

	UChess_GameInstance* GameInstance;

	UPROPERTY()
	UChessHUD* ChessHUD;

	UPROPERTY()
	UPawnPromotionHUD* PawnPromotionHUD;

	// reference to a ChessBoard object
	UPROPERTY(VisibleAnywhere)
	AChessBoard* ChessBoard;

	TArray<ATile*> Piece_SelectableMoves;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsMyTurn = false;

	APiece* SelectedPiece;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnTurn() override;
	virtual void OnWin() override;
	virtual void OnLose() override;

	virtual void OnCheck() override;
	virtual void OnStalemate() override;
	virtual void OnCheckmate() override;


	UFUNCTION()
	void OnClick();
};
