// Fill out your copyright notice in the Description page of Project Settings.


#include "Bishop.h"
#include "ChessBoard.h"

/**
 * @brief ABishop class constructor
 *
 */

ABishop::ABishop() : APiece()
{
	Name = EPieceName::BISHOP;
	Value = 300;
}


/**
 * @brief Compute all the possible moves a bishop can do freely and return it as an array of 2D vector
 *
 * @return array of FVector2D with the moves of the bishop
 */
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


/**
 * @brief This method compute all the avaible moves of the bishop based on his position and his color coded in ETileOwner
 *
 * @param GameField the gamefield
 * @param SameColor color of the bishop coded in ETileOwner
 * @return TArray of ATile pointer with all the tile where the bishop can go
 */
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
				if (UpLeft) //Upleft
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
				if (DownLeft)//DownLeft
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
				if (DownRight)//DownRight
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
				if (UpRight)//UpRight
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

/**
 * @brief This method return the character that identify this piece in the chess notation
 *
 * @return FString with the character that identify this piece in chess notation
 */
FString ABishop::ToString()
{
	return "B";
}

/**
 * @brief AWhiteBishop class constructor
 *
 */
AWhiteBishop::AWhiteBishop() : ABishop()
{
	Color = EPieceColor::WHITE;
}

/**
 * @brief This method is used to return all the avaible moves of the White Bishop piece
 *
 * @param ChessBoard the chessboard where the piece is
 * @return TArray of ATile pointer with all the tile where the White Bishop can go
 */
TArray<ATile*> AWhiteBishop::AvaibleMoves(AChessBoard* ChessBoard)
{
	return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::WHITE);
}

/**
 * @brief ABlackBishop class constructor
 *
 */
ABlackBishop::ABlackBishop() : ABishop()
{
	Color = EPieceColor::BLACK;
}

/**
 * @brief This method is used to return all the avaible moves of the Black Bishop piece
 *
 * @param ChessBoard the chessboard where the piece is
 * @return TArray of ATile pointer with all the tile where the Black Bishop can go
 */
TArray<ATile*> ABlackBishop::AvaibleMoves(AChessBoard* ChessBoard)
{
	return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::BLACK);
}
