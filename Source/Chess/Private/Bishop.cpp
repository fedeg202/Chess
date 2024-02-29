// Fill out your copyright notice in the Description page of Project Settings.


#include "Bishop.h"

TArray<FVector2D> ABishop::Moves()
{
	TArray<FVector2D> Moves;
	const int32 Size = 8;

	// Definisci il vettore base per i movimenti dell'alfiere
	const FVector2D BaseMove1(1, 1);
	const FVector2D BaseMove2(-1, 1);
	const FVector2D BaseMove3(-1, -1);
	const FVector2D BaseMove4(1, -1);

	// Genera i movimenti applicando la trasformazione del vettore base
	for (int32 i = 1; i < Size; ++i)
	{
		Moves.Add(BaseMove1 * i);
		Moves.Add(BaseMove2 * i);
		Moves.Add(BaseMove3 * i);
		Moves.Add(BaseMove4 * i);
	}

	return Moves;
}

TArray<ATile*> ABishop::AvaibleMovesByColor(AGameField* GameField, ETileOwner SameColor)
{
	TArray<ATile*> AvaibleMoves;
	FVector2D CurrentLocation = GetGridPosition();
	TArray<FVector2D> Move = Moves();
	FVector2D tmp_move;

	bool UpRight = true;
	bool DownRight = true;
	bool DownLeft = true;
	bool UpLeft = true;

	int32 upRightNum = 1;
	int32 downRightNum = 2;
	int32 downLeftNum = 3;
	int32 upLeftNum = 4;

	int32 num_move = 1;

	for (int32 i = 0; i < Move.Num(); i++)
	{
		if (num_move > 4) num_move = 1;

		tmp_move = CurrentLocation + Move[i];
		if (tmp_move.X < GameField->Size && tmp_move.Y < GameField->Size && tmp_move.X >= 0 && tmp_move.Y >= 0)
		{
			ATile* tile = GameField->GetTileBYXYPosition(tmp_move.X, tmp_move.Y);
			if (num_move % upLeftNum == 0)
				if (UpLeft) //left
				{
					if (tile->GetTileStatus() == ETileStatus::OCCUPIED)
					{
						if (tile->GetTileOwner() != SameColor)
						{
							AvaibleMoves.Add(tile);
						}
						UpLeft = false;
					}
					else AvaibleMoves.Add(tile);
				}
				else
				{
					num_move++;
					continue;
				}

			else if (num_move % downLeftNum == 0)
				if (DownLeft)
				{
					if (tile->GetTileStatus() == ETileStatus::OCCUPIED)
					{
						if (tile->GetTileOwner() != SameColor)
						{
							AvaibleMoves.Add(tile);
						}
						DownLeft = false;
					}
					else AvaibleMoves.Add(tile);
				}
				else
				{
					num_move++;
					continue;
				}

			else if (num_move % downRightNum == 0)
				if (DownRight)
				{
					if (tile->GetTileStatus() == ETileStatus::OCCUPIED)
					{
						if (tile->GetTileOwner() != SameColor) {
							AvaibleMoves.Add(tile);
						}
						DownRight = false;
					}
					else AvaibleMoves.Add(tile);
				}
				else
				{
					num_move++;
					continue;
				}

			else if (num_move % upRightNum == 0)
				if (UpRight)
				{
					if (tile->GetTileStatus() == ETileStatus::OCCUPIED)
					{
						if (tile->GetTileOwner() != SameColor) {
							AvaibleMoves.Add(tile);
						}
						UpRight = false;
					}
					else AvaibleMoves.Add(tile);
				}
				else
				{
					num_move++;
					continue;
				}

		}
		num_move++;
	}
	return AvaibleMoves;
}

TArray<ATile*> AWhiteBishop::AvaibleMoves(AGameField* GameField)
{
	return AvaibleMovesByColor(GameField, ETileOwner::WHITE);
}

TArray<ATile*> ABlackBishop::AvaibleMoves(AGameField* GameField)
{
	return AvaibleMovesByColor(GameField, ETileOwner::BLACK);
}
