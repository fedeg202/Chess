// Fill out your copyright notice in the Description page of Project Settings.


#include "Queen.h"
#include "ChessBoard.h"

AQueen::AQueen() : APiece()
{
	Name = EPieceName::QUEEN;
}

TArray<FVector2D> AQueen::Moves()
{
	TArray<FVector2D> Moves;
	ABishop Bishop;
	ARook Rook;
	Moves.Append(Bishop.Moves());
	Moves.Append(Rook.Moves());

	return Moves;
}

TArray<ATile*> AQueen::AvaibleMovesByColor(AGameField* GameField, ETileOwner SameColor)
{
	TArray<ATile*> AvaibleMoves;
	FVector2D CurrentLocation = GetGridPosition();
	
	ABishop* Bishop = NewObject<ABishop>(this);  Bishop->SetGridPosition(CurrentLocation.X, CurrentLocation.Y);
	ARook* Rook = NewObject<ARook>(this);		 Rook->SetGridPosition(CurrentLocation.X, CurrentLocation.Y);
			

	AvaibleMoves.Append(Bishop->AvaibleMovesByColor(GameField, SameColor));
	AvaibleMoves.Append(Rook->AvaibleMovesByColor(GameField, SameColor));

	if (Bishop != nullptr) {
		Bishop->Destroy();
	}

	if (Rook != nullptr) {
		Rook->Destroy();
	}

	return AvaibleMoves;
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
