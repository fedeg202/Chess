// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPawn.h"
#include "ChessBoard.h"

AChessPawn::AChessPawn():APiece()
{
	Name = EPieceName::PAWN;
	Value = 10;
}

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

FString AChessPawn::ToString()
{
	return "P";
}

AWhitePawn::AWhitePawn() : AChessPawn()
{
	Color = EPieceColor::WHITE;
}

TArray<ATile*> AWhitePawn::AvaibleMoves(AChessBoard* ChessBoard)
{
	//Useful when using virtual move (it implement a "virtual eaten")
	if (ChessBoard->GetGameField()->GetTileBYXYPosition(GetGridPosition().X, GetGridPosition().Y)->GetTileOwner() != ETileOwner::WHITE)
		return TArray<ATile*>();
	else
		return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::WHITE);
}

ABlackPawn::ABlackPawn() : AChessPawn()
{
	Color = EPieceColor::BLACK;
}

TArray<ATile*> ABlackPawn::AvaibleMoves(AChessBoard* ChessBoard)
{
	//Useful when using virtual move (it implement a "virtual eaten")
	if (ChessBoard->GetGameField()->GetTileBYXYPosition(GetGridPosition().X, GetGridPosition().Y)->GetTileOwner() != ETileOwner::BLACK)
		return TArray<ATile*>();
	else
		return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::BLACK);
}