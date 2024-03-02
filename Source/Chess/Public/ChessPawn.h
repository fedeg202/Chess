// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "ChessPawn.generated.h"


/**
 * 
 */
UCLASS()
class CHESS_API AChessPawn : public APiece
{
	GENERATED_BODY()
public:
	const EPieceName Name = EPieceName::PAWN;
	TArray<FVector2D> Moves() override;
	TArray<ATile*> AvaibleMovesByColor(AGameField* GameField, ETileOwner OpponentColor);
};

UCLASS()
class CHESS_API AWhitePawn : public AChessPawn
{
	GENERATED_BODY()
public:
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
	const EPieceColor Color = EPieceColor::WHITE;
};

UCLASS()
class CHESS_API ABlackPawn : public AChessPawn
{
	GENERATED_BODY()
public:
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
	const EPieceColor Color = EPieceColor::BLACK;
};