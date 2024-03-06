// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Knight.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AKnight : public APiece
{
	GENERATED_BODY()
public:
	AKnight();
	TArray<FVector2D> Moves() override;
	TArray<ATile*> AvaibleMovesByColor(AGameField* GameField, ETileOwner OpponentColor);
};

UCLASS()
class CHESS_API AWhiteKnight : public AKnight
{
	GENERATED_BODY()
public:
	AWhiteKnight();
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};

UCLASS()
class CHESS_API ABlackKnight : public AKnight
{
	GENERATED_BODY()
public:
	ABlackKnight();
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};
