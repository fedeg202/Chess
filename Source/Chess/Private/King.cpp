// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"
#include "ChessBoard.h"

TArray<FVector2D> AKing::Moves()
{
	TArray<FVector2D> Moves;

	const FVector2D BaseMove(1, 0);
	const FVector2D DiagonalMove(1, 1);

	Moves.Add(BaseMove);
	Moves.Add(DiagonalMove);
	Moves.Add(DiagonalMove.GetRotated(-90));

	Moves.Add(-BaseMove);
	Moves.Add(-DiagonalMove);
	Moves.Add(DiagonalMove.GetRotated(+90));

	return Moves;
}

TArray<ATile*> AKing::AvaibleMovesByColor(AChessBoard* ChessBoard, ETileOwner OpponentColor)
{
	int32 Size = ChessBoard->GetGameField()->Size;

	TArray<ATile*> AvaibleMoves;
	FVector2D CurrentLocation = GetGridPosition();
	TArray<FVector2D> Move = Moves();
	FVector2D tmp_move;
	ATile* tile;
	ETileOwner SameColor = ETileOwner::NONE;
	FCoupleTile Tiles;
	APiece* tmp_Piece;

	if (OpponentColor == ETileOwner::BLACK)
		SameColor = ETileOwner::WHITE;
	else
		SameColor = ETileOwner::BLACK;
	

	for (int32 i = 0; i < Move.Num(); i++) {
		tmp_move = CurrentLocation + Move[i];

		if (tmp_move.X < Size && tmp_move.X > 0 && tmp_move.Y < Size && tmp_move.Y > 0) {
			tile = ChessBoard->GetGameField()->GetTileBYXYPosition(tmp_move.X, tmp_move.Y);

			if (tile->GetTileStatus() == ETileStatus::EMPTY || tile->GetTileOwner() == OpponentColor) 
			{
				Tiles.Tile1 = ChessBoard->GetGameField()->GetTileBYXYPosition(CurrentLocation.X, CurrentLocation.Y);
				Tiles.Tile2 = tile;
				tmp_Piece = ChessBoard->VirtualMove(Tiles);
				if (!ChessBoard->CheckOnCheck(SameColor))
					AvaibleMoves.Add(tile);
				ChessBoard->VirtualUnMove(Tiles,tmp);
			}
				

		}
	}

	return AvaibleMoves;
}

TArray<ATile*> AWhiteKing::AvaibleMoves(AChessBoard* ChessBoard)
{
	return AvaibleMovesByColor(ChessBoard, ETileOwner::BLACK);
}

TArray<ATile*> ABlackKing::AvaibleMoves(AChessBoard* ChessBoard)
{
	return AvaibleMovesByColor(ChessBoard, ETileOwner::WHITE);
}