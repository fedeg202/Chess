// Fill out your copyright notice in the Description page of Project Settings.


#include "Rook.h"
#include "ChessBoard.h"

ARook::ARook() : APiece()
{
	Name = EPieceName::ROOK;
	Value = 500;
}

TArray<FVector2D> ARook::Moves()
{
	TArray<FVector2D> Moves;

	
	const int32 Size = 8;
	const FVector2D BaseMove1(1, 0);
	const FVector2D BaseMove2(0, 1);

	
	for (int32 i = 1; i < Size; ++i)
	{
		
		Moves.Add(i * BaseMove1);
		Moves.Add(i * BaseMove2);
		Moves.Add(-i * BaseMove1);
		Moves.Add(-i * BaseMove2);
	}

	return Moves;
}

TArray<ATile*> ARook::AvaibleMovesByColor(AGameField* GameField, ETileOwner SameColor)
{
	TArray<ATile*> AvaibleMoves;
	FVector2D CurrentLocation = GetGridPosition();
	TArray<FVector2D> Move = Moves();
	FVector2D tmp_move;

	bool Up = true;
	bool Right = true;
	bool Down = true;
	bool Left = true;

	int32 upNum = 1;
	int32 rightNum = 2;
	int32 downNum = 3;
	int32 leftNum = 4;

	int32 num_move = 1;

	for (int32 i = 0; i < Move.Num(); i++)
	{
		if (num_move > 4) num_move = 1;

		tmp_move = CurrentLocation + Move[i];
		if (GameField->IsInRange(tmp_move))
		{
			ATile* tile = GameField->GetTileBYXYPosition(tmp_move.X, tmp_move.Y);
			if (num_move % leftNum == 0)
				if (Left) //left
				{
					if (tile->GetTileStatus() == ETileStatus::OCCUPIED)
					{
						if (tile->GetTileOwner() != SameColor)
						{
							AvaibleMoves.Add(tile);
						}
						Left = false;
					}
					else AvaibleMoves.Add(tile);
				}
				else
				{
					num_move++;
					continue;
				}

			else if (num_move % downNum == 0)
				if (Down)
				{
					if (tile->GetTileStatus() == ETileStatus::OCCUPIED)
					{
						if (tile->GetTileOwner() != SameColor)
						{
							AvaibleMoves.Add(tile);
						}
						Down = false;
					}
					else AvaibleMoves.Add(tile);
				}
				else
				{
					num_move++;
					continue;
				}

			else if (num_move % rightNum == 0)
				if (Right)
				{
					if (tile->GetTileStatus() == ETileStatus::OCCUPIED)
					{
						if (tile->GetTileOwner() != SameColor) {
							AvaibleMoves.Add(tile);
						}
						Right = false;
					}
					else AvaibleMoves.Add(tile);
				}
				else
				{
					num_move++;
					continue;
				}

			else if (num_move % upNum == 0)
				if (Up)
				{
					if (tile->GetTileStatus() == ETileStatus::OCCUPIED)
					{
						if (tile->GetTileOwner() != SameColor) {
							AvaibleMoves.Add(tile);
						}
						Up = false;
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

FString ARook::ToString()
{
	return "R";
}

AWhiteRook::AWhiteRook() : ARook()
{
	Color = EPieceColor::WHITE;
}

TArray<ATile*> AWhiteRook::AvaibleMoves(AChessBoard* ChessBoard)
{
	//Utile in combo con virtual move
	if (ChessBoard->GetGameField()->GetTileBYXYPosition(GetGridPosition().X, GetGridPosition().Y)->GetTileOwner() != ETileOwner::WHITE)
		return TArray<ATile*>();
	else
		return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::WHITE);

}

ABlackRook::ABlackRook() : ARook()
{
	Color = EPieceColor::BLACK;
}

TArray<ATile*> ABlackRook::AvaibleMoves(AChessBoard* ChessBoard)
{
	//Utile in combo con virtual move
	if (ChessBoard->GetGameField()->GetTileBYXYPosition(GetGridPosition().X, GetGridPosition().Y)->GetTileOwner() != ETileOwner::BLACK)
		return TArray<ATile*>();
	else
		return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::BLACK);
}
