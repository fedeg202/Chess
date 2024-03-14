// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"
#include "ChessBoard.h"

AKing::AKing() : APiece()
{
	Name = EPieceName::KING;
}

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

TArray<ATile*> AKing::AvaibleMovesByColor(AChessBoard* ChessBoard, ETileOwner OpponentColor)
{
	int32 Size = ChessBoard->GetGameField()->Size;

	TArray<ATile*> AvaibleMoves;
	FVector2D CurrentLocation = GetGridPosition();
	TArray<FVector2D> Move = Moves();
	FVector2D tmp_move;
	ATile* tile;
	ETileOwner SameColor = ETileOwner::NONE;

	if (OpponentColor == ETileOwner::BLACK)
		SameColor = ETileOwner::WHITE;
	else
		SameColor = ETileOwner::BLACK;
	

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

FString AKing::ToString()
{
	return "K";
}

AWhiteKing::AWhiteKing() : AKing()
{
	Color = EPieceColor::WHITE;
}

TArray<ATile*> AWhiteKing::AvaibleMoves(AChessBoard* ChessBoard)
{
	return AvaibleMovesByColor(ChessBoard, ETileOwner::BLACK);
}

ABlackKing::ABlackKing() : AKing()
{
	Color = EPieceColor::BLACK;
}

TArray<ATile*> ABlackKing::AvaibleMoves(AChessBoard* ChessBoard)
{
	return AvaibleMovesByColor(ChessBoard, ETileOwner::WHITE);
}