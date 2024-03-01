// Fill out your copyright notice in the Description page of Project Settings.


#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"

TArray<FVector2D> AQueen::Moves()
{
	TArray<FVector2D> Moves;
	ABishop Bishop;
	ARook Rook;
	Moves.Append(Bishop.Moves());
	Moves.Append(Rook.Moves());

	return Moves;
}

TArray<ATile*> AQueen::AvaibleMovesByColor(AGameField* GameField, ETileOwner SameColor)
{
	TArray<ATile*> AvaibleMoves;
	FVector2D CurrentLocation = GetGridPosition();
	
	ABishop Bishop; Bishop.SetGridPosition(CurrentLocation.X, CurrentLocation.Y);
	ARook Rook; Rook.SetGridPosition(CurrentLocation.X, CurrentLocation.Y);

	AvaibleMoves.Append(Bishop.AvaibleMovesByColor(GameField, SameColor));
	AvaibleMoves.Append(Rook.AvaibleMovesByColor(GameField, SameColor));

	return AvaibleMoves;
}

TArray<ATile*> AWhiteQueen::AvaibleMoves(AGameField* GameField)
{
	return AvaibleMovesByColor(GameField, ETileOwner::WHITE);
}

TArray<ATile*> ABlackQueen::AvaibleMoves(AGameField* GameField)
{
	return AvaibleMovesByColor(GameField, ETileOwner::BLACK);
}
