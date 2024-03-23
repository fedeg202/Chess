// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Rook.generated.h"

/**
 * Classes to implement the rook piece, that inherit from the generic piece class
 */
UCLASS()
class CHESS_API ARook : public APiece
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ARook();
	//Return all the moves as a 2D vector, that a generic rook can do freely
	TArray<FVector2D> Moves() override;
	//Return a pointer to all the tiles where the rook can go, based on the color coded in the ETileOwner
	TArray<ATile*> AvaibleMovesByColor(AGameField* GameField, ETileOwner SameColor);
	//Method to obtain the string that rapresent this piece in the move notation
	FString ToString() override;

};

UCLASS()
class CHESS_API AWhiteRook : public ARook
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AWhiteRook();
	//Return a pointer to all the tiles where WHite the rook can go 
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};

UCLASS()
class CHESS_API ABlackRook : public ARook
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABlackRook();
	//Return a pointer to all the tiles where the Black rook can go
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};