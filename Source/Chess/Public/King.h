// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "King.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AKing : public APiece
{
	GENERATED_BODY()
	GENERATED_BODY()
public:
	TArray<FVector2D> Moves() override;
	TArray<ATile*> AvaibleMovesByColor(AGameField* GameField, ETileOwner OpponentColor);

};

UCLASS()
class CHESS_API AWhiteKing : public AKing
{
	GENERATED_BODY()
public:
	virtual TArray<ATile*> AvaibleMoves(AGameField* GameField) override;
};

UCLASS()
class CHESS_API ABlackKing : public AKing
{
	GENERATED_BODY()
public:
	virtual TArray<ATile*> AvaibleMoves(AGameField* GameField) override;
};

