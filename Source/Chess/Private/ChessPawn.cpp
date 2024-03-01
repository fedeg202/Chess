// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPawn.h"

TArray<FVector2D> AChessPawn::Moves()
{
	TArray<FVector2D> Moves;

	// Definisci il vettore base per i movimenti del cavallo
	const FVector2D BaseMove(1, 0);
	const FVector2D EatMove(1, 1);
	
	Moves.Add(BaseMove);
	Moves.Add(2 * BaseMove);
	Moves.Add(EatMove);
	Moves.Add(EatMove.GetRotated(-90));

	Moves.Add(-BaseMove);
	Moves.Add(-2 * BaseMove);
	Moves.Add(-EatMove);
	Moves.Add(EatMove.GetRotated(+90));

	return Moves;
}

TArray<ATile*> AChessPawn::AvaibleMovesByColor(AGameField* GameField, ETileOwner OpponentColor)
{
	int32 Size = GameField->Size;

	int32 startMove;
	int32 startPos;
	if (OpponentColor == ETileOwner::WHITE)
	{
		startMove = 4;
		startPos = Size - 2;
		
	}
	else
	{
		startMove = 0;
		startPos = 1;
	}
	TArray<ATile*> AvaibleMoves;
	FVector2D CurrentLocation = GetGridPosition();
	TArray<FVector2D> Move = Moves();
	FVector2D tmp_move;
	

	tmp_move = CurrentLocation + Move[startMove];
	if (tmp_move.X < Size && tmp_move.X >= 0)
	{
		ATile* tile = GameField->GetTileBYXYPosition(tmp_move.X, tmp_move.Y);
		if (tile->GetTileStatus() == ETileStatus::EMPTY)
			AvaibleMoves.Add(tile);
	}

	if (CurrentLocation.X == startPos)
	{
		tmp_move = CurrentLocation + Move[startMove+1];
		ATile* tile = GameField->GetTileBYXYPosition(tmp_move.X, tmp_move.Y);
		if (tile->GetTileStatus() == ETileStatus::EMPTY && AvaibleMoves.Num()>0)
			AvaibleMoves.Add(tile);
	}

	tmp_move = CurrentLocation + Move[startMove + 2];
	if (tmp_move.X < Size && tmp_move.X > 0 && tmp_move.Y < Size && tmp_move.Y > 0)
	{
		ATile* tile = GameField->GetTileBYXYPosition(tmp_move.X, tmp_move.Y);
		if (tile->GetTileStatus() == ETileStatus::OCCUPIED && tile->GetTileOwner() == OpponentColor)
			AvaibleMoves.Add(tile);
	}

	tmp_move = CurrentLocation + Move[startMove + 3];
	if (tmp_move.X < Size && tmp_move.X > 0 && tmp_move.Y < Size && tmp_move.Y)
	{
		ATile* tile = GameField->GetTileBYXYPosition(tmp_move.X, tmp_move.Y);
		if (tile->GetTileStatus() == ETileStatus::OCCUPIED && tile->GetTileOwner() == OpponentColor)
			AvaibleMoves.Add(tile);
	}

	return AvaibleMoves;
}

TArray<ATile*> AWhitePawn::AvaibleMoves(AGameField* GameField)
{
	return AvaibleMovesByColor(GameField, ETileOwner::BLACK);
}

TArray<ATile*> ABlackPawn::AvaibleMoves(AGameField* GameField)
{
	return AvaibleMovesByColor(GameField, ETileOwner::WHITE);
}