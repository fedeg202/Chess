// Fill out your copyright notice in the Description page of Project Settings.


#include "Queen.h"
#include "ChessBoard.h"

/**
 * @brief AQueen class constructor
 *
 */
AQueen::AQueen() : APiece()
{
	Name = EPieceName::QUEEN;
	Value = 1000;
}

/**
 * @brief Compute all the possible moves a queen can do freely and return it as an array of 2D vector
 *
 * @return array of FVector2D with the moves of the queen
 */
TArray<FVector2D> AQueen::Moves()
{
	TArray<FVector2D> Moves;
	TArray<FVector2D> BaseMoves;


	const int32 Size = 8;
	BaseMoves.Add(FVector2D(1, 0));
	BaseMoves.Add(FVector2D(-1, 0));
	BaseMoves.Add(FVector2D(0, 1));
	BaseMoves.Add(FVector2D(0, -1));
	BaseMoves.Add(FVector2D(1, 1));
	BaseMoves.Add(FVector2D(-1, -1));
	BaseMoves.Add(FVector2D(-1, 1));
	BaseMoves.Add(FVector2D(1, -1));

	for (int32 j = 0; j < BaseMoves.Num(); j++)
	{
		for (int32 i = 1; i < Size; i++)
		{
			Moves.Add(i * BaseMoves[j]);
		}
	}
	return Moves;
}

/**
 * @brief This method compute all the avaible moves of the queen based on his position and his color coded in ETileOwner
 *
 * @param GameField the gamefield
 * @param SameColor color of the queen coded in ETileOwner
 * @return TArray of ATile pointer with all the tile where the queen can go
 */
TArray<ATile*> AQueen::AvaibleMovesByColor(AGameField* GameField, ETileOwner SameColor)
{
	TArray<ATile*> AvaibleMoves;
	TArray<FVector2D> Move = Moves();
	FVector2D tmp_move;
	FVector2D CurrentLocation = GetGridPosition();


	for (int32 j = 0; j < 8; j++)
	{
		bool b_IsOKDirection = true;
		for (int32 i = 0; i < 7; i++)
		{
			if (b_IsOKDirection)
			{
				tmp_move = CurrentLocation + Move[i + j*7];
				if (GameField->IsInRange(tmp_move))
				{
					ATile* tile = GameField->GetTileBYXYPosition(tmp_move.X, tmp_move.Y);
					if (tile->GetTileStatus() == ETileStatus::OCCUPIED)
					{
						if (tile->GetTileOwner() != SameColor)
						{
							AvaibleMoves.Add(tile);
						}
						b_IsOKDirection = false;
					}
					else AvaibleMoves.Add(tile);
				}
			}
			else break;
		}
	}

	return AvaibleMoves;
}

/**
 * @brief This method return the character that identify this piece in the chess notation
 *
 * @return FString with the character that identify this piece in chess notation
 */
FString AQueen::ToString()
{
	return "Q";
}

/**
 * @brief AWhiteQueen class contructor
 *
 */
AWhiteQueen::AWhiteQueen() : AQueen()
{
	Color = EPieceColor::WHITE;
}

/**
 * @brief This method is used to return all the avaible moves of the White Queen piece
 *
 * @param ChessBoard the chessboard where the piece is
 * @return TArray of ATile pointer with all the tile where the White Queen can go
 */
TArray<ATile*> AWhiteQueen::AvaibleMoves(AChessBoard* ChessBoard)
{
	//Utile in combo con virtual move
	if (ChessBoard->GetGameField()->GetTileBYXYPosition(GetGridPosition().X, GetGridPosition().Y)->GetTileOwner() != ETileOwner::WHITE)
		return TArray<ATile*>();
	else
		return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::WHITE);
}

/**
 * @brief ABlackQueen class contructor
 *
 */
ABlackQueen::ABlackQueen() : AQueen()
{
	Color = EPieceColor::BLACK;
}

/**
 * @brief This method is used to return all the avaible moves of the Black Queen piece
 *
 * @param ChessBoard the chessboard where the piece is
 * @return TArray of ATile pointer with all the tile where the Black Queen can go
 */
TArray<ATile*> ABlackQueen::AvaibleMoves(AChessBoard* ChessBoard)
{
	//Utile in combo con virtual move
	if (ChessBoard->GetGameField()->GetTileBYXYPosition(GetGridPosition().X, GetGridPosition().Y)->GetTileOwner() != ETileOwner::BLACK)
		return TArray<ATile*>();
	else
		return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::BLACK);
}
