// Fill out your copyright notice in the Description page of Project Settings.


#include "Bishop.h"
#include "ChessBoard.h"

ABishop::ABishop() : APiece()
{
	Name = EPieceName::BISHOP;
}

TArray<FVector2D> ABishop::Moves()
{
	TArray<FVector2D> Moves;
	const int32 Size = 8;

	const FVector2D BaseMove1(1, 1);
	const FVector2D BaseMove2(-1, 1);
	const FVector2D BaseMove3(-1, -1);
	const FVector2D BaseMove4(1, -1);

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
		if (GameField->IsInRange(tmp_move))
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

FString ABishop::ToString()
{
	return "B";
}

AWhiteBishop::AWhiteBishop() : ABishop()
{
	Color = EPieceColor::WHITE;
}

TArray<ATile*> AWhiteBishop::AvaibleMoves(AChessBoard* ChessBoard)
{
	//Utile in combo con virtual move
	if (ChessBoard->GetGameField()->GetTileBYXYPosition(GetGridPosition().X, GetGridPosition().Y)->GetTileOwner() != ETileOwner::WHITE)
		return TArray<ATile*>();
	else
		return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::WHITE);
}

ABlackBishop::ABlackBishop() : ABishop()
{
	Color = EPieceColor::BLACK;
}

TArray<ATile*> ABlackBishop::AvaibleMoves(AChessBoard* ChessBoard)
{
	//Utile in combo con virtual move
	if (ChessBoard->GetGameField()->GetTileBYXYPosition(GetGridPosition().X, GetGridPosition().Y)->GetTileOwner() != ETileOwner::BLACK)
		return TArray<ATile*>();
	else
		return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::BLACK);
}
