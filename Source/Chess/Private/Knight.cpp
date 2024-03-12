// Fill out your copyright notice in the Description page of Project Settings.


#include "Knight.h"
#include "ChessBoard.h"


AKnight::AKnight() : APiece()
{
	Name = EPieceName::KNIGHT;
}

TArray<FVector2D> AKnight::Moves()
{
	TArray<FVector2D> Moves;

	// Definisci il vettore base per i movimenti del cavallo
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


AWhiteKnight::AWhiteKnight():AKnight()
{
	Color = EPieceColor::WHITE;
}

TArray<ATile*> AWhiteKnight::AvaibleMoves(AChessBoard* ChessBoard)
{
	//Utile in combo con virtual move
	if (ChessBoard->GetGameField()->GetTileBYXYPosition(GetGridPosition().X, GetGridPosition().Y)->GetTileOwner() != ETileOwner::WHITE)
		return TArray<ATile*>();
	else
		return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::WHITE);
}

ABlackKnight::ABlackKnight() : AKnight()
{
	Color = EPieceColor::BLACK;
}

TArray<ATile*> ABlackKnight::AvaibleMoves(AChessBoard* ChessBoard)
{
	//Utile in combo con virtual move
	if (ChessBoard->GetGameField()->GetTileBYXYPosition(GetGridPosition().X, GetGridPosition().Y)->GetTileOwner() != ETileOwner::BLACK)
		return TArray<ATile*>();
	else
		return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::BLACK);
}