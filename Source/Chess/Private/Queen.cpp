// Fill out your copyright notice in the Description page of Project Settings.


#include "Queen.h"
#include "ChessBoard.h"

AQueen::AQueen() : APiece()
{
	Name = EPieceName::QUEEN;
	Value = 1000;
}

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

FString AQueen::ToString()
{
	return "Q";
}

AWhiteQueen::AWhiteQueen() : AQueen()
{
	Color = EPieceColor::WHITE;
}

TArray<ATile*> AWhiteQueen::AvaibleMoves(AChessBoard* ChessBoard)
{
	//Utile in combo con virtual move
	if (ChessBoard->GetGameField()->GetTileBYXYPosition(GetGridPosition().X, GetGridPosition().Y)->GetTileOwner() != ETileOwner::WHITE)
		return TArray<ATile*>();
	else
		return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::WHITE);
}

ABlackQueen::ABlackQueen() : AQueen()
{
	Color = EPieceColor::BLACK;
}

TArray<ATile*> ABlackQueen::AvaibleMoves(AChessBoard* ChessBoard)
{
	//Utile in combo con virtual move
	if (ChessBoard->GetGameField()->GetTileBYXYPosition(GetGridPosition().X, GetGridPosition().Y)->GetTileOwner() != ETileOwner::BLACK)
		return TArray<ATile*>();
	else
		return AvaibleMovesByColor(ChessBoard->GetGameField(), ETileOwner::BLACK);
}
