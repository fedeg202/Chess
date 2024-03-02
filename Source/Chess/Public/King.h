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
	const EPieceName Name = EPieceName::KING;
	TArray<FVector2D> Moves() override;
	TArray<ATile*> AvaibleMovesByColor(AChessBoard* ChessBoard, ETileOwner OpponentColor);

};

UCLASS()
class CHESS_API AWhiteKing : public AKing
{
	GENERATED_BODY()
public:
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
	const EPieceColor Color = EPieceColor::WHITE;
};

UCLASS()
class CHESS_API ABlackKing : public AKing
{
	GENERATED_BODY()
public:
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
	const EPieceColor Color = EPieceColor::BLACK;
};

