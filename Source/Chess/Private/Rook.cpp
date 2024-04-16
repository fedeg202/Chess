// Fill out your copyright notice in the Description page of Project Settings.


#include "Rook.h"
#include "ChessBoard.h"

/**
 * @brief ARook class constructor
 *
 */
ARook::ARook() : APiece()
{
	Name = EPieceName::ROOK;
	Value = 500;
}

/**
 * @brief Compute all the possible moves a rook can do freely and return it as an array of 2D vector
 *
 * @return array of FVector2D with the moves of the rook
 */
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

/**
 * @brief This method compute all the avaible moves of the rook based on his position and his color coded in ETileOwner
 *
 * @param GameField the gamefield
 * @param SameColor color of the queen coded in ETileOwner
 * @return TArray of ATile pointer with all the tile where the rook can go
 */
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

/**
 * @brief This method return the character that identify this piece in the chess notation
 *
 * @return FString with the character that identify this piece in chess notation
 */
FString ARook::ToString()
{
	return "R";
}

/**
 * @brief AWhiteRook class contructor
 *
 */
AWhiteRook::AWhiteRook() : ARook()
{
	Color = EPieceColor::WHITE;
}

/**
 * @brief This method is used to return all the avaible moves of the White Rook piece
 *
 * @param ChessBoard the chessboard where the piece is
 * @return TArray of ATile pointer with all the tile where the White Rook can go
 */
TArray<ATile*> AWhiteRook::AvaibleMoves(AChessBoard* ChessBoard)
{
		return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::WHITE);
}

/**
 * @brief ABlackRook class contructor
 *
 */
ABlackRook::ABlackRook() : ARook()
{
	Color = EPieceColor::BLACK;
}

/**
 * @brief This method is used to return all the avaible moves of the Black Rook piece
 *
 * @param ChessBoard the chessboard where the piece is
 * @return TArray of ATile pointer with all the tile where the Black Rook can go
 */
TArray<ATile*> ABlackRook::AvaibleMoves(AChessBoard* ChessBoard)
{
	return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::BLACK);
}
