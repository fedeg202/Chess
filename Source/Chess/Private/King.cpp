// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"

TArray<FVector2D> AKing::Moves()
{
	TArray<FVector2D> Moves;

	const FVector2D BaseMove(1, 0);
	const FVector2D DiagonalMove(1, 1);

	Moves.Add(BaseMove);
	Moves.Add(2 * BaseMove);
	Moves.Add(DiagonalMove);
	Moves.Add(DiagonalMove.GetRotated(-90));

	Moves.Add(-BaseMove);
	Moves.Add(-2 * BaseMove);
	Moves.Add(-DiagonalMove);
	Moves.Add(DiagonalMove.GetRotated(+90));

	return Moves;
}

TArray<ATile*> AKing::AvaibleMovesByColor(AGameField* GameField, ETileOwner OpponentColor)
{
	int32 Size = GameField->Size;

	TArray<ATile*> AvaibleMoves;
	FVector2D CurrentLocation = GetGridPosition();
	TArray<FVector2D> Move = Moves();
	FVector2D tmp_move;
	ATile* tile;

	for (int32 i = 0; i < Move.Num(); i++) {
		tmp_move = CurrentLocation + Move[i];

		if (tmp_move.X < Size && tmp_move.X > 0 && tmp_move.Y < Size && tmp_move.Y > 0) {
			tile = GameField->GetTileBYXYPosition(tmp_move.X, tmp_move.Y);
			if (tile->GetTileStatus() == ETileStatus::EMPTY || tile->GetTileOwner() == OpponentColor)
				AvaibleMoves.Add(tile);

		}
	}

	return AvaibleMoves;
}

TArray<ATile*> AWhiteKing::AvaibleMoves(AGameField* GameField)
{
	return AvaibleMovesByColor(GameField, ETileOwner::BLACK);
}

TArray<ATile*> ABlackKing::AvaibleMoves(AGameField* GameField)
{
	return AvaibleMovesByColor(GameField, ETileOwner::WHITE);
}