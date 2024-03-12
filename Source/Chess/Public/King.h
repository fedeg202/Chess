// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "King.generated.h"

/**
 * Classes to implement the king piece, that inherit from the generic piece class
 */
UCLASS()
class CHESS_API AKing : public APiece
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AKing();
	//Return all the moves as a 2D vector, that a generic king can do freely
	TArray<FVector2D> Moves() override;
	//Return a pointer to all the tiles where the king can go, based on the color coded in the ETileOwner
	TArray<ATile*> AvaibleMovesByColor(AChessBoard* ChessBoard, ETileOwner OpponentColor);

};

UCLASS()
class CHESS_API AWhiteKing : public AKing
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AWhiteKing();
	//Return a pointer to all the tiles where the white king can go
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};

UCLASS()
class CHESS_API ABlackKing : public AKing
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABlackKing();
	//Return a pointer to all the tiles where the black king can go
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard) override;
};

