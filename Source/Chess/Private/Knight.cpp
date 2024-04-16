// Fill out your copyright notice in the Description page of Project Settings.


#include "Knight.h"
#include "ChessBoard.h"


/**
 * @brief AKnight class constructor
 *
 */
AKnight::AKnight() : APiece()
{
	Name = EPieceName::KNIGHT;
	Value = 300;
}

/**
 * @brief Compute all the possible moves a knight can do freely and return it as an array of 2D vector
 *
 * @return array of FVector2D with the moves of the knight
 */
TArray<FVector2D> AKnight::Moves()
{
	TArray<FVector2D> Moves;

	const FVector2D BaseMove1(2,1);
	const FVector2D BaseMove2(2, -1);
	const FVector2D BaseMove3(1, 2);
	const FVector2D BaseMove4(-1, 2);

	Moves.Add(BaseMove1);
	Moves.Add(BaseMove2);
	Moves.Add(BaseMove3);
	Moves.Add(BaseMove4);

	Moves.Add(-BaseMove1);
	Moves.Add(-BaseMove2);
	Moves.Add(-BaseMove3);
	Moves.Add(-BaseMove4);

	return Moves;
}

/**
 * @brief This method compute all the avaible moves of the knight based on his position and his color coded in ETileOwner
 *
 * @param GameField the gamefield
 * @param SameColor color of the knight coded in ETileOwner
 * @return TArray of ATile pointer with all the tile where the knight can go
 */
TArray<ATile*> AKnight::AvaibleMovesByColor(AGameField* GameField, ETileOwner SameColor)
{
	TArray<ATile*> AvaibleMoves;
	FVector2D CurrentLocation = GetGridPosition();
	TArray<FVector2D> Move = Moves();
	FVector2D tmp_move;
	for (int32 i = 0; i < Move.Num(); i++)
	{
		tmp_move = CurrentLocation + Move[i];
		if (GameField->IsInRange(tmp_move))
		{
			ATile* tile = GameField->GetTileBYXYPosition(tmp_move.X, tmp_move.Y);
			if (tile->GetTileOwner() != SameColor) {
				AvaibleMoves.Add(tile);
			}
		}
	}

	return AvaibleMoves;
}

/**
 * @brief This method return the character that identify this piece in the chess notation
 *
 * @return FString with the character that identify this piece in chess notation
 */
FString AKnight::ToString()
{
	return "N";
}

/**
 * @brief AWhiteKnight class constructor
 *
 */
AWhiteKnight::AWhiteKnight():AKnight()
{
	Color = EPieceColor::WHITE;
}

/**
 * @brief This method is used to return all the avaible moves of the White Knight piece
 *
 * @param ChessBoard the chessboard where the piece is
 * @return TArray of ATile pointer with all the tile where the White Knight can go
 */
TArray<ATile*> AWhiteKnight::AvaibleMoves(AChessBoard* ChessBoard)
{
	return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::WHITE);
}

/**
 * @brief ABlackKnight class constructor
 *
 */
ABlackKnight::ABlackKnight() : AKnight()
{
	Color = EPieceColor::BLACK;
}

/**
 * @brief This method is used to return all the avaible moves of the Black Knight piece
 *
 * @param ChessBoard the chessboard where the piece is
 * @return TArray of ATile pointer with all the tile where the Black Knight can go
 */
TArray<ATile*> ABlackKnight::AvaibleMoves(AChessBoard* ChessBoard)
{
	return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::BLACK);
}