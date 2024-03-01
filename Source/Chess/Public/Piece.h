// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameField.h"
class AChessBoard;

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Piece.generated.h"

UCLASS()
class CHESS_API APiece : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APiece();

	void SetGridPosition(const double x, const double y);

	FVector2D GetGridPosition();

	virtual TArray<FVector2D> Moves();

	void Eat(ATile* EatTile, AChessBoard* ChessBoard);

	virtual TArray<ATile*> AvaibleMoves(AGameField* GameField);

	void Move(ATile* Tile, AGameField* GameField);

	APiece* GetPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
	FVector2D PieceGridPosition;
};
