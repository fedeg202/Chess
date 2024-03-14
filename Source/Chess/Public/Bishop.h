// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Bishop.generated.h"

/**
 *  Classes to implement the bishop piece, that inherit from the generic piece class
 */
UCLASS()
class CHESS_API ABishop : public APiece
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABishop();
	//Return all the moves as a 2D vector, that a generic bishop can do freely
	TArray<FVector2D> Moves() override;
	//Return a pointer to all the tiles where the bishop can go, based on the color coded in the ETileOwner
	TArray<ATile*> AvaibleMovesByColor(AGameField* GameField, ETileOwner SameColor);

	FString ToString() override;
};

UCLASS()
class CHESS_API AWhiteBishop : public ABishop
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AWhiteBishop();
	//Return a pointer to all the tiles where the white bishop can go
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;

};

UCLASS()
class CHESS_API ABlackBishop : public ABishop
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABlackBishop();
	//Return a pointer to all the tiles where the black bishop can go
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};
