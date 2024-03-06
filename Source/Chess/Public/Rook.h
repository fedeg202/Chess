// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Rook.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API ARook : public APiece
{
	GENERATED_BODY()
public:
	ARook();
	TArray<FVector2D> Moves() override;
	TArray<ATile*> AvaibleMovesByColor(AGameField* GameField, ETileOwner SameColor);


};

UCLASS()
class CHESS_API AWhiteRook : public ARook
{
	GENERATED_BODY()
public:
	AWhiteRook();
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};

UCLASS()
class CHESS_API ABlackRook : public ARook
{
	GENERATED_BODY()
public:
	ABlackRook();
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};