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
	TArray<FVector2D> Moves() override;
	TArray<ATile*> AvaibleMovesByColor(AGameField* GameField, ETileOwner SameColor);
protected:
	EPieceName Name = EPieceName::BISHOP;
};

UCLASS()
class CHESS_API AWhiteBishop : public ABishop
{
	GENERATED_BODY()
public:
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
protected:
	EPieceColor Color = EPieceColor::WHITE;
};

UCLASS()
class CHESS_API ABlackBishop : public ABishop
{
	GENERATED_BODY()
public:
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
protected:
	EPieceColor Color = EPieceColor::BLACK;
};
