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
public:
	AKing();
	TArray<FVector2D> Moves() override;
	TArray<ATile*> AvaibleMovesByColor(AChessBoard* ChessBoard, ETileOwner OpponentColor);

};

UCLASS()
class CHESS_API AWhiteKing : public AKing
{
	GENERATED_BODY()
public:
	AWhiteKing();
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};

UCLASS()
class CHESS_API ABlackKing : public AKing
{
	GENERATED_BODY()
public:
	ABlackKing();
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};

