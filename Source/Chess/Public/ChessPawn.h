// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "ChessPawn.generated.h"


/**
 * Classes to implement the pawn piece, that inherit from the generic piece class
 */
UCLASS()
class CHESS_API AChessPawn : public APiece
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AChessPawn();
	//Return all the moves as a 2D vector, that a generic pawn can do freely
	TArray<FVector2D> Moves() override;
	//Return a pointer to all the tiles where the pawn can go, based on the color coded in the ETileOwner
	TArray<ATile*> AvaibleMovesByColor(AGameField* GameField, ETileOwner OpponentColor);
};

UCLASS()
class CHESS_API AWhitePawn : public AChessPawn
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AWhitePawn();
	//Return a pointer to all the tiles where the white pawn can go
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};

UCLASS()
class CHESS_API ABlackPawn : public AChessPawn
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABlackPawn();
	//Return a pointer to all the tiles where the black pawn can go
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};