// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Queen.generated.h"

/**
 * @brief Class to implement the queen piece, that inherit from the generic piece class
 */
UCLASS()
class CHESS_API AQueen : public APiece
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AQueen();
	//Return all the moves as a 2D vector, that a generic queen can do freely
	TArray<FVector2D> Moves() override;
	//Return a pointer to all the tiles where the queen can go, based on the color coded in the ETileOwner
	TArray<ATile*> AvaibleMovesByColor(AGameField* GameField, ETileOwner SameColor);
	//Method to obtain the string that rapresent this piece in the move notation
	FString ToString() override;

};

/**
 * @brief Class to implement the white queen piece, that inherit from the AQueen class
 */
UCLASS()
class CHESS_API AWhiteQueen : public AQueen
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AWhiteQueen();
	//Return a pointer to all the tiles where the white queen can go
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};

/**
 * @brief Class to implement the black queen piece, that inherit from the AQueen class
 */
UCLASS()
class CHESS_API ABlackQueen : public AQueen
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABlackQueen();
	//Return a pointer to all the tiles where the black queen can go
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};

