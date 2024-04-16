// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPawn.h"
#include "ChessBoard.h"

/**
 * @brief AChessPawn class constructor
 *
 */
AChessPawn::AChessPawn():APiece()
{
	Name = EPieceName::PAWN;
	Value = 100;
}

/**
 * @brief Compute all the possible moves a pawn can do freely and return it as an array of 2D vector
 *
 * @return array of FVector2D with the moves of the pawn
 */
TArray<FVector2D> AChessPawn::Moves()
{
	TArray<FVector2D> Moves;

	// 
	const FVector2D BaseMove(1, 0);
	const FVector2D EatMove1(1, 1);
	const FVector2D EatMove2(1, -1);
	
	Moves.Add(BaseMove);
	Moves.Add(2 * BaseMove);
	Moves.Add(EatMove1);
	Moves.Add(EatMove2);

	Moves.Add(-BaseMove);
	Moves.Add(-2 * BaseMove);
	Moves.Add(-EatMove1);
	Moves.Add(-EatMove2);

	return Moves;
}

/**
 * @brief This method compute all the avaible moves of the pawn based on his position and his color coded in ETileOwner
 *
 * @param GameField the gamefield
 * @param SameColor color of the pawn coded in ETileOwner
 * @return TArray of ATile pointer with all the tile where the pawn can go
 */
TArray<ATile*> AChessPawn::AvaibleMovesByColor(AGameField* GameField, ETileOwner SameColor)
{
	int32 Size = GameField->Size;
	int32 startMove;
	int32 startPos;
	ETileOwner OpponentColor;
	if (SameColor == ETileOwner::WHITE)
	{
		OpponentColor = ETileOwner::BLACK;
		startMove = 0;
		startPos = 1;
	}
	else
	{
		OpponentColor = ETileOwner::WHITE;
		startMove = 4;
		startPos = Size - 2;
	}
	TArray<ATile*> AvaibleMoves;
	FVector2D CurrentLocation = GetGridPosition();
	TArray<FVector2D> Move = Moves();
	FVector2D tmp_move;
	

	tmp_move = CurrentLocation + Move[startMove];
	if (GameField->IsInRange(tmp_move))
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
	if (GameField->IsInRange(tmp_move))
	{
		ATile* tile = GameField->GetTileBYXYPosition(tmp_move.X, tmp_move.Y);
		if (tile->GetTileStatus() == ETileStatus::OCCUPIED && tile->GetTileOwner() == OpponentColor)
			AvaibleMoves.Add(tile);
	}

	tmp_move = CurrentLocation + Move[startMove + 3];
	if (GameField->IsInRange(tmp_move))
	{
		ATile* tile = GameField->GetTileBYXYPosition(tmp_move.X, tmp_move.Y);
		if (tile->GetTileStatus() == ETileStatus::OCCUPIED && tile->GetTileOwner() == OpponentColor)
			AvaibleMoves.Add(tile);
	}

	return AvaibleMoves;
}

/**
 * @brief This method return the character that identify this piece in the chess notation
 *
 * @return FString with the character that identify this piece in chess notation
 */
FString AChessPawn::ToString()
{
	return "P";
}

/**
 * @brief AWhitePawn class constructor
 *
 */
AWhitePawn::AWhitePawn() : AChessPawn()
{
	Color = EPieceColor::WHITE;
}

/**
 * @brief This method is used to return all the avaible moves of the White Pawn piece
 *
 * @param ChessBoard the chessboard where the piece is
 * @return TArray of ATile pointer with all the tile where the White Pawn can go
 */
TArray<ATile*> AWhitePawn::AvaibleMoves(AChessBoard* ChessBoard)
{
	return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::WHITE);
}

/**
 * @brief ABlackPawn class constructor
 *
 */
ABlackPawn::ABlackPawn() : AChessPawn()
{
	Color = EPieceColor::BLACK;
}

/**
 * @brief This method is used to return all the avaible moves of the Black Pawn piece
 *
 * @param ChessBoard the chessboard where the piece is
 * @return TArray of ATile pointer with all the tile where the Black Pawn can go
 */
TArray<ATile*> ABlackPawn::AvaibleMoves(AChessBoard* ChessBoard)
{
	return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::BLACK);
}