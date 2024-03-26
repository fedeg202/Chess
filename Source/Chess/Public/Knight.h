// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Knight.generated.h"

/**
 *  Classes to implement the knight piece, that inherit from the generic piece class
 */
UCLASS()
class CHESS_API AKnight : public APiece
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AKnight();
	//Return all the moves as a 2D vector, that a generic knight can do freely
	TArray<FVector2D> Moves() override;
	//Return a pointer to all the tiles where the knight can go, based on the color coded in the ETileOwner
	TArray<ATile*> AvaibleMovesByColor(AGameField* GameField, ETileOwner OpponentColor);
	//Method to obtain the string that rapresent this piece in the move notation
	FString ToString() override;
};

UCLASS()
class CHESS_API AWhiteKnight : public AKnight
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AWhiteKnight();
	//Return a pointer to all the tiles where the white knight can go
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};

UCLASS()
class CHESS_API ABlackKnight : public AKnight
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABlackKnight();
	//Return a pointer to all the tiles where the black knight can go
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};
