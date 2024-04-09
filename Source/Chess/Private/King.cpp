// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"
#include "ChessBoard.h"

/**
 * @brief AKing class constructor
 *
 */
AKing::AKing() : APiece()
{
	Name = EPieceName::KING;
}

/**
 * @brief Compute all the possible moves a king can do freely and return it as an array of 2D vector
 *
 * @return array of FVector2D with the moves of the king
 */
TArray<FVector2D> AKing::Moves()
{
	TArray<FVector2D> Moves;

	const FVector2D BaseMove(1, 0);
	const FVector2D DiagonalMove1(1, 1);
	const FVector2D DiagonalMove2(1, -1);

	Moves.Add(BaseMove);
	Moves.Add(BaseMove.GetRotated(-90));
	Moves.Add(DiagonalMove1);
	Moves.Add(DiagonalMove2);

	Moves.Add(-BaseMove);
	Moves.Add(BaseMove.GetRotated(+90));
	Moves.Add(-DiagonalMove1);
	Moves.Add(-DiagonalMove2);

	return Moves;
}

/**
 * @brief This method compute all the avaible moves of the king based on his position and his color coded in ETileOwner
 *
 * @param GameField the gamefield
 * @param SameColor color of the king coded in ETileOwner
 * @return TArray of ATile pointer with all the tile where the king can go
 */
TArray<ATile*> AKing::AvaibleMovesByColor(AChessBoard* ChessBoard, ETileOwner SameColor)
{
	int32 Size = ChessBoard->GetGameField()->Size;

	TArray<ATile*> AvaibleMoves;
	FVector2D CurrentLocation = GetGridPosition();
	TArray<FVector2D> Move = Moves();
	FVector2D tmp_move;
	ATile* tile;
	ETileOwner OpponentColor = ETileOwner::NONE;

	if (SameColor == ETileOwner::BLACK)
		OpponentColor = ETileOwner::WHITE;
	else
		OpponentColor = ETileOwner::BLACK;
	

	for (int32 i = 0; i < Move.Num(); i++) {
		tmp_move = CurrentLocation + Move[i];

		if (ChessBoard->GetGameField()->IsInRange(tmp_move)) {
			tile = ChessBoard->GetGameField()->GetTileBYXYPosition(tmp_move.X, tmp_move.Y);

			if (tile->GetTileStatus() == ETileStatus::EMPTY || tile->GetTileOwner() == OpponentColor) 
			{
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
FString AKing::ToString()
{
	return "K";
}

/**
 * @brief AWhiteKing class constructor
 *
 */
AWhiteKing::AWhiteKing() : AKing()
{
	Color = EPieceColor::WHITE;
}
/**
 * @brief This method is used to return all the avaible moves of the White King piece
 *
 * @param ChessBoard the chessboard where the piece is
 * @return TArray of ATile pointer with all the tile where the White King can go
 */
TArray<ATile*> AWhiteKing::AvaibleMoves(AChessBoard* ChessBoard)
{
	return AvaibleMovesByColor(ChessBoard, ETileOwner::WHITE);
}

/**
 * @brief ABlackKing class constructor
 *
 */
ABlackKing::ABlackKing() : AKing()
{
	Color = EPieceColor::BLACK;
}

/**
 * @brief This method is used to return all the avaible moves of the Black King piece
 *
 * @param ChessBoard the chessboard where the piece is
 * @return TArray of ATile pointer with all the tile where the Black King can go
 */
TArray<ATile*> ABlackKing::AvaibleMoves(AChessBoard* ChessBoard)
{
	return AvaibleMovesByColor(ChessBoard, ETileOwner::BLACK);
}