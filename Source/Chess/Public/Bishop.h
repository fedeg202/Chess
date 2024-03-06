// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Bishop.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API ABishop : public APiece
{
	GENERATED_BODY()
public:
	ABishop();
	TArray<FVector2D> Moves() override;
	TArray<ATile*> AvaibleMovesByColor(AGameField* GameField, ETileOwner SameColor);
};

UCLASS()
class CHESS_API AWhiteBishop : public ABishop
{
	GENERATED_BODY()
public:
	AWhiteBishop();
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;

};

UCLASS()
class CHESS_API ABlackBishop : public ABishop
{
	GENERATED_BODY()
public:
	ABlackBishop();
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};
