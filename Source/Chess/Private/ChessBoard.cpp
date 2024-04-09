// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessBoard.h"
#include "Chess_PlayerController.h"
#include "ChessGameMode.h"

/*
* @brief AChessBoard class constructor
*/

AChessBoard::AChessBoard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WhitePieces.SetNum(0);
	EatenWhitePieces.SetNum(0);

	BlackPieces.SetNum(0);
	EatenBlackPieces.SetNum(0);

}

/*
* @brief Getter of the array of the white pieces
* 
* @return reference to the array of the white pieces
*/
TArray<APiece*>& AChessBoard::GetWhitePieces()
{
	return WhitePieces;
}
/*
* @brief Getter of the array of the eaten white pieces
*
* @return reference to the array of the eaten white pieces
*/
TArray<APiece*>& AChessBoard::GetEatenWhitePieces()
{
	return EatenWhitePieces;
}
/*
* @brief Getter of the array of the black pieces
*
* @return reference to the array of the black pieces
*/
TArray<APiece*>& AChessBoard::GetBlackPieces()
{
	return BlackPieces;
}
/*
* @brief Getter of the array of the eaten black pieces
*
* @return reference to the array of the eaten black pieces
*/
TArray<APiece*>& AChessBoard::GetEatenBlackPieces()
{
	return EatenBlackPieces;
}

/*
* @brief Method to obtain the array of pieces based on the color coded in the SameColor parameter
* 
* @param SameColor color of the piece that you want to obtain
* 
* @return reference to the array of the chosen color piece
*/
TArray<APiece*>& AChessBoard::GetPiecesByColor(ETileOwner SameColor)
{
	if (SameColor == ETileOwner::BLACK) return GetBlackPieces();
	else return GetWhitePieces();
}

/*
* @brief Getter of the GameField
* 
* @return reference to the GameField
*/
AGameField* AChessBoard::GetGameField()
{
	return GameField;
}

/*
* @brief Method to spawn the game field (all the tiles)
*
*/
void AChessBoard::SpawnGameField()
{
	FVector Location(0, 0, 0);
	GameField = GetWorld()->SpawnActor<AGameField>(GameFieldClass, Location, FRotator::ZeroRotator);
}

/*
* @brief Method to spawn all the white pieces at the start of the game or when resetting
*
*/
void AChessBoard::SpawnWhitePieces()
{
	int32 x = 1;
	int32 y = 0;
	APiece* Obj;
	FVector Location;
	FVector ZOffset = FVector(0, 0, 10);
	for (y = 0; y < GameField->Size; y++)
	{
		Location = GameField->GetRelativeLocationByXYPosition(x, y) + ZOffset;
		Obj = GetWorld()->SpawnActor<AWhitePawn>(WhitePawnClass, Location, FRotator::ZeroRotator);
		Obj->SetGridPosition(x, y);
		GameField->GetTileBYXYPosition(x, y)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::WHITE, Obj);
		WhitePieces.Add(Obj);
	}
	x--;


	y = 0;
	Location = GameField->GetRelativeLocationByXYPosition(x, y) + ZOffset;
	Obj = GetWorld()->SpawnActor<AWhiteRook>(WhiteRookClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x, y)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::WHITE, Obj);
	WhitePieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size - y - 1) + ZOffset;
	Obj = GetWorld()->SpawnActor<AWhiteRook>(WhiteRookClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x, GameField->Size - y - 1)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::WHITE, Obj);
	WhitePieces.Add(Obj);


	y = 1;
	Location = GameField->GetRelativeLocationByXYPosition(x, y) + ZOffset;
	Obj = GetWorld()->SpawnActor<AWhiteKnight>(WhiteKnightClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x, y)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::WHITE, Obj);
	WhitePieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size - y - 1) + ZOffset;
	Obj = GetWorld()->SpawnActor<AWhiteKnight>(WhiteKnightClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x, GameField->Size - y - 1)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::WHITE, Obj);
	WhitePieces.Add(Obj);

	y = 2;
	Location = GameField->GetRelativeLocationByXYPosition(x, y) + ZOffset;
	Obj = GetWorld()->SpawnActor<AWhiteBishop>(WhiteBishopClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x, y)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::WHITE, Obj);
	WhitePieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size - y - 1) + ZOffset;
	Obj = GetWorld()->SpawnActor<AWhiteBishop>(WhiteBishopClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x, GameField->Size - y - 1)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::WHITE, Obj);
	WhitePieces.Add(Obj);

	y = 3;
	Location = GameField->GetRelativeLocationByXYPosition(x, y) + ZOffset;
	Obj = GetWorld()->SpawnActor<AWhiteQueen>(WhiteQueenClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x, y)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::WHITE, Obj);
	WhitePieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size - y - 1) + ZOffset;
	Obj = GetWorld()->SpawnActor<AWhiteKing>(WhiteKingClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x, GameField->Size - y - 1)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::WHITE, Obj);
	WhitePieces.Add(Obj);
}

/*
* @brief Method to spawn all the black pieces at the start of the game or when resetting
*
*/
void AChessBoard::SpawnBlackPieces()
{
	int32 x = GameField->Size - 2;
	int32 y = 0;
	APiece* Obj;
	FVector Location;
	FVector ZOffset = FVector(0, 0, 10);
	for (y = 0; y < GameField->Size; y++)
	{
		Location = GameField->GetRelativeLocationByXYPosition(x, y) + ZOffset;
		Obj = GetWorld()->SpawnActor<ABlackPawn>(BlackPawnClass, Location, FRotator::ZeroRotator);
		Obj->SetGridPosition(x, y);
		GameField->GetTileBYXYPosition(x, y)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::BLACK, Obj);
		BlackPieces.Add(Obj);
	}
	x++;

	y = 0;
	Location = GameField->GetRelativeLocationByXYPosition(x, y) + ZOffset;
	Obj = GetWorld()->SpawnActor<ABlackRook>(BlackRookClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x, y)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::BLACK, Obj);
	BlackPieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size- y - 1) + ZOffset;
	Obj = GetWorld()->SpawnActor<ABlackRook>(BlackRookClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x, GameField->Size - y - 1)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::BLACK, Obj);
	BlackPieces.Add(Obj);


	y = 1;
	Location = GameField->GetRelativeLocationByXYPosition(x, y) + ZOffset;
	Obj = GetWorld()->SpawnActor<ABlackKnight>(BlackKnightClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x, y)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::BLACK, Obj);
	BlackPieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size - y - 1) + ZOffset;
	Obj = GetWorld()->SpawnActor<ABlackKnight>(BlackKnightClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x, GameField->Size - y - 1)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::BLACK, Obj);
	BlackPieces.Add(Obj);

	
	y = 2;
	Location = GameField->GetRelativeLocationByXYPosition(x, y) + ZOffset;
	Obj = GetWorld()->SpawnActor<ABlackBishop>(BlackBishopClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x, y)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::BLACK, Obj);
	BlackPieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size - y - 1) + ZOffset;
	Obj = GetWorld()->SpawnActor<ABlackBishop>(BlackBishopClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x, GameField->Size - y - 1)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::BLACK, Obj);
	BlackPieces.Add(Obj);


	y = 3;
	Location = GameField->GetRelativeLocationByXYPosition(x, y) + ZOffset;
	Obj = GetWorld()->SpawnActor<ABlackQueen>(BlackQueenClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x, y)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::BLACK, Obj);
	BlackPieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size - y - 1) + ZOffset;
	Obj = GetWorld()->SpawnActor<ABlackKing>(BlackKingClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x, GameField->Size - y - 1)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::BLACK, Obj);
	BlackPieces.Add(Obj);

}

/*
* @brief Method to show all the selectable tile by changing the material to make them different from the others
* 
* @param SelectableTiles array of reference to tiles that you want to be "marked" as selectable
*/
void AChessBoard::ShowSelectableTiles(TArray<ATile*>& SelectableTiles)
{
	ATile* Tile;
	for (int32 i = 0; i < SelectableTiles.Num(); i++)
	{
		Tile = SelectableTiles[i];
		ETileStatus status = Tile->GetTileStatus();
		if (status == ETileStatus::EMPTY)
		{
			Tile->SetTileStatus(ETileStatus::SELECTABLE);
			Tile->SetTileMaterial(1);
		}
		else if (status == ETileStatus::OCCUPIED) 
		{
			Tile->SetTileStatus(ETileStatus::EATABLE);
			Tile->SetTileMaterial(2);
		}

	}
}

/*
* @brief Method to unshow all the selectable tile by changing the material to make them different from the others
*
* @param SelectableTiles array of reference to tiles that you want to be restored to the state before been "marked" as selectable
*/
void AChessBoard::UnShowSelectableTiles(TArray<ATile*>& SelectableTiles)
{
	ATile* Tile;
	for (int32 i = 0; i < SelectableTiles.Num(); i++)
	{
		Tile = SelectableTiles[i];
		ETileStatus status = Tile->GetTileStatus();
		if (status == ETileStatus::SELECTABLE)
		{
			Tile->SetTileStatus(ETileStatus::EMPTY);
		}
		else if (status == ETileStatus::EATABLE)
		{
			Tile->SetTileStatus(ETileStatus::OCCUPIED);
		}
		Tile->SetTileMaterial(0);
	}
}

/*
* @brief Method to add a piece to the white piece array, and to handle the visibility of the pieces in that array
*
* @param EatenPiece pointer to the piece that you want to add
*/
void AChessBoard::AddWhiteEatenPiece(APiece* EatenPiece)
{
	if (EatenWhitePieces.IsEmpty())
		EatenWhitePieces.Push(EatenPiece);
	else 
	{
		EatenWhitePieces.Top()->SetActorHiddenInGame(true);
		EatenWhitePieces.Push(EatenPiece);
	}
}

/*
* @brief Method to add a piece to the black piece array, and to handle the visibility of the pieces in that array
*
* @param EatenPiece pointer to the piece that you want to add
*/
void AChessBoard::AddBlackEatenPiece(APiece* EatenPiece)
{
	if (EatenBlackPieces.IsEmpty())
		EatenBlackPieces.Push(EatenPiece);
	else
	{
		EatenBlackPieces.Top()->SetActorHiddenInGame(true);
		EatenBlackPieces.Push(EatenPiece);
	}
}

/*
* @brief Method to pop a white piece from the white eaten piece array, and to handle the visibility of the pieces in that array
*
* @return pointer to the piece that has been popped
*/
APiece* AChessBoard::PopWhiteEatenPiece()
{
	if (EatenWhitePieces.Num() > 1)
	{
		
		APiece* Piece = EatenWhitePieces.Pop(true);
		EatenWhitePieces.Top()->SetActorHiddenInGame(false);
		return Piece;
	}
	else
		return EatenWhitePieces.Pop(true);
		
}

/*
* @brief Method to pop a piece from the black eaten piece array, and to handle the visibility of the piece in that array
*
* @return pointer to the piece that has been popped
*/
APiece* AChessBoard::PopBlackEatenPiece()
{
	if (EatenBlackPieces.Num() > 1)
	{
		APiece* Piece = EatenBlackPieces.Pop(true);
		EatenBlackPieces.Top()->SetActorHiddenInGame(false);
		return Piece;
	}
	else
		return EatenBlackPieces.Pop(true);
}

/*
* @brief Method to check if the king of the player with the color coded in the SameColor parameter is in check
*
* @param SameColor color of the player that you want to control the state of ckeck of the king
* @return true if it is on check, false if it isn't
*/
bool AChessBoard::CheckOnCheck(ETileOwner SameColor)
{
	TArray<FCoupleTile> AllOpponentSelectableMoves;

	if (SameColor == ETileOwner::BLACK) 
	{
		AllOpponentSelectableMoves = AllWhiteSelectableMoves;
	}
	else {
		AllOpponentSelectableMoves = AllBlackSelectableMoves;
	}

	for (int32 i = 0; i < AllOpponentSelectableMoves.Num(); i++)
	{
		if (AllOpponentSelectableMoves[i].Tile2->GetOnPiece() != nullptr 
			&& AllOpponentSelectableMoves[i].Tile2->GetOnPiece()->GetName() == EPieceName::KING)
			return true;
	}

	return false;
}

/*
* @brief Method to check if the king of the player with the color coded in the SameColor parameter is in check, based on the moves of the other player in the Tmp_moves array
*
* @param Tmp_Moves moves of the opponent of the player you want to check if is in check
* @return true if it is on check, false if it isn't
*/
bool AChessBoard::CheckOnCheck(TArray<FCoupleTile> Tmp_Moves)
{
	for (int32 i = 0; i < Tmp_Moves.Num(); i++)
	{
		if (Tmp_Moves[i].Tile2->GetOnPiece() != nullptr
			&& Tmp_Moves[i].Tile2->GetOnPiece()->GetName() == EPieceName::KING)
			return true;
	}
	return false;
}

/*
* @brief Method to check if the king of the player with the color coded in the SameColor parameter is in stalemate
*
* @param SameColor color of the player that you want to control the state of ckeck of the king
* @return true if it is on stalemate, false if it isn't
*/
bool AChessBoard::CheckOnStalemate(ETileOwner SameColor)
{
	if (SameColor == ETileOwner::BLACK)
		if (AllBlackSelectableMoves.Num() == 0) return true;
		else return false;
	else
		if (AllWhiteSelectableMoves.Num() == 0) return true;
		else return false;
}

/*
* @brief Method to make a "virtual" move, changing the state of the chessboard as the piece actually moved but without graphically moving the actor
*
* @param Tiles tiles that are involved in the move
* @return a pointer to the eventual "virtual eaten" piece, nullptr if there is no eaten piece
*/
APiece* AChessBoard::VirtualMove(FCoupleTile Tiles)
{
	APiece* OldOnPiece = Tiles.Tile2->GetOnPiece();
	Tiles.Tile2->SetStatusAndOwnerAndOnPiece(Tiles.Tile1->GetTileStatus(), Tiles.Tile1->GetTileOwner(), Tiles.Tile1->GetOnPiece());

	if (Tiles.Tile1->GetOnPiece() == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Mannaggia è null pointer"));
	}

	Tiles.Tile1->GetOnPiece()->SetGridPosition(Tiles.Tile2->GetGridPosition());

	Tiles.Tile1->SetStatusAndOwnerAndOnPiece(ETileStatus::EMPTY, ETileOwner::NONE, nullptr);

	if (OldOnPiece != nullptr)
	{
		if (OldOnPiece->GetColor() == EPieceColor::BLACK)
			GetBlackPieces().Remove(OldOnPiece);
		else if (OldOnPiece->GetColor() == EPieceColor::WHITE)
			GetWhitePieces().Remove(OldOnPiece);
	}

	return OldOnPiece;
}

/*
* @brief Method to unmake a "virtual" move, reverting the state of the chessboard to bring it back before the virtual move
*
* @param OldOnPiece the eventually eaten piece that is needed to be bringed beck in the actual game
* 
*/
void AChessBoard::VirtualUnMove(FCoupleTile Tiles, APiece* OldOnPiece)
{
	ETileStatus Status;
	ETileOwner TileOwner;

	Tiles.Tile1->SetStatusAndOwnerAndOnPiece(Tiles.Tile2->GetTileStatus(), Tiles.Tile2->GetTileOwner(), Tiles.Tile2->GetOnPiece());

	if (Tiles.Tile2->GetOnPiece() == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Warning,is a null pointer"));
	}
	

	Tiles.Tile2->GetOnPiece()->SetGridPosition(Tiles.Tile1->GetGridPosition());

	if (OldOnPiece != nullptr)
	{
		Status = ETileStatus::OCCUPIED;
		if (OldOnPiece->GetColor() == EPieceColor::BLACK)
		{
			TileOwner = ETileOwner::BLACK;
			GetBlackPieces().Add(OldOnPiece);
		}	
		else if (OldOnPiece->GetColor() == EPieceColor::WHITE)
		{
			TileOwner = ETileOwner::WHITE;
			GetWhitePieces().Add(OldOnPiece);
		}
	}
	else 
	{
		Status = ETileStatus::EMPTY;
		TileOwner = ETileOwner::NONE;
	}

	Tiles.Tile2->SetStatusAndOwnerAndOnPiece(Status, TileOwner, OldOnPiece);
}

/*
* @brief Method to compute all the possible moves of the player that has the piece of the color coded in the Color parameter, and put it in the correct attribute of the chessboard class
*
* @param Color color of the pieces that you want to compute the moves of
*
*/
void AChessBoard::UpdateAllMoveBYColor(ETileOwner Color)
{
	TArray<APiece*> ColorPieces;
	TArray<FCoupleTile> AllColorSelectableMoves;
	TArray<FCoupleTile> AllOppositeColorMoves;
	TArray<ATile*> APieceSelectableMoves;
	FCoupleTile CoupleTile_tmp;
	APiece* tmp_piece;
	TArray<ATile*> TilesToRemove;
	ETileOwner OppositeColor;

	if (Color == ETileOwner::BLACK) 
	{
		ColorPieces = GetBlackPieces();
		OppositeColor = ETileOwner::WHITE;
	}	
	else
	{
		ColorPieces = GetWhitePieces();
		OppositeColor = ETileOwner::BLACK;
	}
		

	for (int32 i = 0; i < ColorPieces.Num(); i++) 
	{
		CoupleTile_tmp.Tile1 = GetGameField()->GetTileBYXYPosition(ColorPieces[i]->GetGridPosition().X, ColorPieces[i]->GetGridPosition().Y);
		APieceSelectableMoves = ColorPieces[i]->AvaibleMoves(this);
		for (int32 j = 0; j < APieceSelectableMoves.Num(); j++)
		{
			CoupleTile_tmp.Tile2 = APieceSelectableMoves[j];

			if (CoupleTile_tmp.Tile1->GetOnPiece() == nullptr)
			{
				UE_LOG(LogTemp, Display, TEXT("Warning is a null pointer"));
			}

			tmp_piece = VirtualMove(CoupleTile_tmp);
			AllOppositeColorMoves = GetAllMovesByColor(OppositeColor);
			if (CheckOnCheck(AllOppositeColorMoves))
				TilesToRemove.Add(APieceSelectableMoves[j]);
			VirtualUnMove(CoupleTile_tmp, tmp_piece);
		}

		for (int32 j = 0; j < TilesToRemove.Num(); j++)
		{
			APieceSelectableMoves.Remove(TilesToRemove[j]);
		}

		TilesToRemove.Empty();

		for (int32 j = 0; j < APieceSelectableMoves.Num(); j++) 
		{
			CoupleTile_tmp.Tile2 = APieceSelectableMoves[j];
			AllColorSelectableMoves.Add(CoupleTile_tmp);
		}
	}

	if (Color == ETileOwner::BLACK)
		AllBlackSelectableMoves = AllColorSelectableMoves;
	else
		AllWhiteSelectableMoves = AllColorSelectableMoves;


}

/*
* @brief Getter of the attribute All*color*SelectableMoves of the class based on the SameColor parameter
*
* @param SameColor color of the pieces that you want to have all selectable move of
* @return reference to an array of FCoupleTile with all the moves of the chosen color
*/
TArray<FCoupleTile>& AChessBoard::GetAllSelectableMovesByColor(ETileOwner SameColor)
{
	if (SameColor == ETileOwner::BLACK)
		return AllBlackSelectableMoves;
	else return AllWhiteSelectableMoves;
}

/*
* @brief Method to get a copy of the attribute All*color*SelectableMoves of the class based on the SameColor parameter
*
* @param SameColor color of the pieces that you want to have all selectable move of
* @param bCopy bool to assure that you want to use this method instead of the normal getter
* @return reference to an array of FCoupleTile with all the selectable moves of the chosen color
*/
TArray<FCoupleTile> AChessBoard::GetAllSelectableMovesByColor(ETileOwner SameColor, bool bCopy) const
{
	TArray<FCoupleTile> Moves;
	if (SameColor == ETileOwner::BLACK)
		Moves = AllBlackSelectableMoves;
	else Moves = AllWhiteSelectableMoves;
	TArray<FCoupleTile> CopyMoves;
	for (int32 i = 0; i < Moves.Num(); i++)
	{
		CopyMoves.Add(FCoupleTile(Moves[i]));
	}
	return CopyMoves;
}

/*
* @brief Method to obtainall the moves of the player with the color coded in the SameColor parameter, the difference between the AllMoves and the
*		 AllSelectableMoves is that the AllMoves are also the one that put you own king in check, that are not allowed in the chess rules
*
* @param SameColor color of the pieces that you want to have all move of
* @return an array of FCoupleTile with all the moves of the chosen color
*/
TArray<FCoupleTile> AChessBoard::GetAllMovesByColor(ETileOwner SameColor)
{
	TArray<APiece*> ColorPieces;
	TArray<FCoupleTile> AllColorMoves;
	TArray<ATile*> APieceSelectableMoves;
	FCoupleTile CoupleTile_tmp;

	if (SameColor == ETileOwner::BLACK)
	{
		ColorPieces = GetBlackPieces();
	}
	else
	{
		ColorPieces = GetWhitePieces();
	}


	for (int32 i = 0; i < ColorPieces.Num(); i++)
	{
		CoupleTile_tmp.Tile1 = GetGameField()->GetTileBYXYPosition(ColorPieces[i]->GetGridPosition().X, ColorPieces[i]->GetGridPosition().Y);
		APieceSelectableMoves = ColorPieces[i]->AvaibleMoves(this);
		
		for (int32 j = 0; j < APieceSelectableMoves.Num(); j++)
		{
			CoupleTile_tmp.Tile2 = APieceSelectableMoves[j];
			AllColorMoves.Add(CoupleTile_tmp);
		}
	}
	
	return AllColorMoves;
}

/*
* @brief Method to reset the chessboard to its starting state
*
*/
void AChessBoard::ResetChessBoard()
{
	GameField->ResetField();

	for (int32 i = 0; i < BlackPieces.Num(); i++)
	{
		BlackPieces[i]->Destroy();
	}
	BlackPieces.Empty();

	for (int32 i = 0; i < EatenBlackPieces.Num(); i++)
	{
		EatenBlackPieces[i]->Destroy();
	}
	EatenBlackPieces.Empty();

	for (int32 i = 0; i < WhitePieces.Num(); i++)
	{
		WhitePieces[i]->Destroy();
	}
	WhitePieces.Empty();

	for (int32 i = 0; i < EatenWhitePieces.Num(); i++)
	{
		EatenWhitePieces[i]->Destroy();
	}
	EatenWhitePieces.Empty();

	AllMoves.Empty();

	StateOccurrences.Empty();

	SpawnBlackPieces();
	SpawnWhitePieces();

}

/*
* @brief Method check if the piece passed as a parameter is elegible for a pawn promotion
* 
* @param Piece pointer to the piece that you want to check
* @return true if the piece is a pawn and reached the opposite end of the gamefield, false otherwise
*/
bool AChessBoard::CheckPawnPromotion(APiece* Piece)
{
	return Piece->GetName() == EPieceName::PAWN && ((Piece->GetColor() == EPieceColor::WHITE && Piece->GetGridPosition().X == GetGameField()->Size - 1) || (Piece->GetColor() == EPieceColor::BLACK && Piece->GetGridPosition().X == 0));
}

/*
* @brief Method check if one of the piece with the color passed as a parameter is elegible for a pawn promotion
*
* @param Color color of the piece that you want to check
* @return true if there is a pawn on the opposite end compared to the start, false otherwise
*/
bool AChessBoard::CheckPawnPromotion(ETileOwner Color)
{
	if (Color == ETileOwner::BLACK)
	{
		for (int32 i = 0; i < GetGameField()->Size-1; i++)
		{
			if (GetGameField()->GetTileBYXYPosition(0, i)->GetOnPiece() != nullptr && GetGameField()->GetTileBYXYPosition(0, i)->GetOnPiece()->GetName() == EPieceName::PAWN) return true;
		}
		return false;
	}
	else
	{
		for (int32 i = 0; i < GetGameField()->Size - 1; i++)
		{
			if (GetGameField()->GetTileBYXYPosition(GetGameField()->Size - 1, i)->GetOnPiece() != nullptr && GetGameField()->GetTileBYXYPosition(GetGameField()->Size - 1, i)->GetOnPiece()->GetName() == EPieceName::PAWN) return true;
		}
		return false;
	}
}

/*
* @brief Method create a string that describe the move with the Long Algebraic Notation
* 
* @param Piece that made the move
* @param Tiles tiles involved in the move
* @param b_eatFlag boolean value to keep track if the move involved an eating of a piece
* @param b_promotionFlag boolean value to keep track if the move involved a pawn promotion
* @return string with the move coded in the long algerbraic notation
*/
FString AChessBoard::CreateMoveString(APiece* Piece, FCoupleTile Tiles, bool b_eatFlag, bool b_promotionFlag)
{
	FString Result;
	FString Eat;
	FString Promotion;
	FString Check;
	if (b_eatFlag)
		Eat = "x";
	else
		Eat = "-";

	if (b_promotionFlag)
		Promotion = "=";
	else
		Promotion = "";

	Result = Piece->ToString() + Tiles.Tile1->ToString() + Eat + Tiles.Tile2->ToString() + Promotion;

	return Result;
}

/*
* @brief Method to push a move to the AllMoves array that contains all the move of the game
*
* @param Move the move to be added
*/
void AChessBoard::AddMove(FMove Move)
{
	AllMoves.Push(Move);
}

/*
* @brief Getter of the AllMoves array by reference
*
*/
TArray<FMove>& AChessBoard::GetAllMoves()
{
	return AllMoves;
}

/*
* @brief Method to restore the chessboard going backward to a state identified by an index in the allmoves array
*
* @param CurrentMoveIndex the index from where the chessboard starts
* @param TargetMoveIndex the index that is the target
*/
void AChessBoard::RestoreChessboardToMoveBackward(int32 CurrentMoveIndex,int32 TargetMoveindex)
{
	for (int32 i = CurrentMoveIndex; i > TargetMoveindex; i--)
	{
		StateOccurrences[GetChessboardStateString()]--;
		if (!AllMoves[i].bEatFlag && !AllMoves[i].bPawnPromotion)
		{
			APiece* Piece = AllMoves[i].Tiles.Tile2->GetOnPiece();
			Piece->Move(AllMoves[i].Tiles.Tile1,this->GetGameField());
		}
		else if (AllMoves[i].bEatFlag && AllMoves[i].bPawnPromotion)
		{
			APiece* Piece = AllMoves[i].Tiles.Tile2->GetOnPiece();
			FVector2D GridPosition = Piece->GetGridPosition();
			FVector Location = AGameField::GetRelativeLocationByXYPosition(GridPosition.X, GridPosition.Y);
			APiece* Pawn;
			APiece* EatenPiece;
			FVector EatenLocation;
			
			if (AllMoves[i].Player == EColor::BLACK)
			{
				EatenPiece = PopWhiteEatenPiece();
				WhitePieces.Add(EatenPiece);
				
				BlackPieces.Remove(Piece);
				Piece->Destroy();
				Pawn = GetWorld()->SpawnActor<ABlackPawn>(BlackPawnClass, Location, FRotator::ZeroRotator);
				Pawn->SetGridPosition(GridPosition.X,GridPosition.Y);
				AllMoves[i].Tiles.Tile2->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::BLACK,Pawn);
				BlackPieces.Add(Pawn);

				Pawn->Move(AllMoves[i].Tiles.Tile1, this->GetGameField());

				this->GetGameField()->GetTileBYXYPosition(EatenPiece->GetGridPosition().X, EatenPiece->GetGridPosition().Y)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::WHITE, EatenPiece);
			}
			else
			{
				EatenPiece = PopBlackEatenPiece();
				BlackPieces.Add(EatenPiece);

				WhitePieces.Remove(Piece);
				Piece->Destroy();
				Pawn = GetWorld()->SpawnActor<AWhitePawn>(WhitePawnClass, Location, FRotator::ZeroRotator);
				Pawn->SetGridPosition(GridPosition.X, GridPosition.Y);
				AllMoves[i].Tiles.Tile2->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::WHITE, Pawn);
				WhitePieces.Add(Pawn);

				Pawn->Move(AllMoves[i].Tiles.Tile1, this->GetGameField());

				this->GetGameField()->GetTileBYXYPosition(EatenPiece->GetGridPosition().X, EatenPiece->GetGridPosition().Y)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::BLACK, EatenPiece);
			}

			EatenLocation = AGameField::GetRelativeLocationByXYPosition(EatenPiece->GetGridPosition().X, EatenPiece->GetGridPosition().Y);
			EatenPiece->SetActorLocation(EatenLocation);
		}
		else if (AllMoves[i].bEatFlag && !AllMoves[i].bPawnPromotion)
		{
			APiece* Piece = AllMoves[i].Tiles.Tile2->GetOnPiece();
			APiece* EatenPiece;
			FVector EatenLocation;

			if (AllMoves[i].Player == EColor::BLACK)
			{
				EatenPiece = PopWhiteEatenPiece();
				WhitePieces.Add(EatenPiece);

				Piece->Move(AllMoves[i].Tiles.Tile1, this->GetGameField());

				this->GetGameField()->GetTileBYXYPosition(EatenPiece->GetGridPosition().X, EatenPiece->GetGridPosition().Y)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::WHITE, EatenPiece);
			}
			else
			{
				EatenPiece = PopBlackEatenPiece();
				BlackPieces.Add(EatenPiece);

				Piece->Move(AllMoves[i].Tiles.Tile1, this->GetGameField());

				this->GetGameField()->GetTileBYXYPosition(EatenPiece->GetGridPosition().X, EatenPiece->GetGridPosition().Y)->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::BLACK, EatenPiece);
			}

			EatenLocation = AGameField::GetRelativeLocationByXYPosition(EatenPiece->GetGridPosition().X, EatenPiece->GetGridPosition().Y);
			EatenPiece->SetActorLocation(EatenLocation);
		}
		else if (!AllMoves[i].bEatFlag && AllMoves[i].bPawnPromotion)
		{
			APiece* Piece = AllMoves[i].Tiles.Tile2->GetOnPiece();
			FVector2D GridPosition = Piece->GetGridPosition();
			FVector Location = AGameField::GetRelativeLocationByXYPosition(GridPosition.X, GridPosition.Y);
			APiece* Pawn;

			if (AllMoves[i].Player == EColor::BLACK)
			{
				BlackPieces.Remove(Piece);
				Piece->Destroy();
				Pawn = GetWorld()->SpawnActor<ABlackPawn>(BlackPawnClass, Location, FRotator::ZeroRotator);
				Pawn->SetGridPosition(GridPosition.X, GridPosition.Y);
				AllMoves[i].Tiles.Tile2->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::BLACK, Pawn);
				BlackPieces.Add(Pawn);

				Pawn->Move(AllMoves[i].Tiles.Tile1, this->GetGameField());
			}
			else
			{
				WhitePieces.Remove(Piece);
				Piece->Destroy();
				Pawn = GetWorld()->SpawnActor<AWhitePawn>(WhitePawnClass, Location, FRotator::ZeroRotator);
				Pawn->SetGridPosition(GridPosition.X, GridPosition.Y);
				AllMoves[i].Tiles.Tile2->SetStatusAndOwnerAndOnPiece(ETileStatus::OCCUPIED, ETileOwner::WHITE, Pawn);
				WhitePieces.Add(Pawn);

				Pawn->Move(AllMoves[i].Tiles.Tile1, this->GetGameField());
			}
		}
	}
}

/*
* @brief Method to restore the chessboard going forward to a state identified by an index in the allmoves array
*
* @param CurrentMoveIndex the index from where the chessboard starts
* @param TargetMoveIndex the index that is the target
*/
void AChessBoard::RestoreChessboardToMoveForward(int32 CurrentMoveindex, int32 TargetMoveIndex)
{
	for (int32 i = CurrentMoveindex; i <= TargetMoveIndex; i++)
	{
		StateOccurrences[GetChessboardStateString()]++;
		if (AllMoves[i].bEatFlag)
			AllMoves[i].Tiles.Tile1->GetOnPiece()->Eat(AllMoves[i].Tiles.Tile2, this);
		else
			AllMoves[i].Tiles.Tile1->GetOnPiece()->Move(AllMoves[i].Tiles.Tile2, this->GetGameField());
		if (AllMoves[i].bPawnPromotion)
		{
			EPieceColor Color;
			if (AllMoves[i].Player == EColor::WHITE) Color = EPieceColor::WHITE;
			else Color = EPieceColor::BLACK;
			AChessGameMode* GameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());
			GameMode->HandlePawnPromotion(Color, AllMoves[i].PawnPromotedTo,false);
		}
			
	}
}

/*
* @brief Getter of the top element of the AllMoves array
* 
* @return reference the top element of the AllMoves array
*/
FMove& AChessBoard::GetTopMove()
{
	return AllMoves.Top();
}

/*
* @brief Method to remove all the move from the AllMoves array that have an index bigger than the parameter one
*
* @param StartingIndex the index from where starting to remove elements
*/
void AChessBoard::RemoveMovesFromStartingIndex(int32 StartingIndex)
{
	int32 i = AllMoves.Num()-1;
	for (; i > StartingIndex; i = AllMoves.Num() - 1)
	{
		AllMoves.Pop();
	}
}

/*
* @brief Method to obtain a string that describe the state of the chessboard to keep track of all the occurences of the state in the match
*
* @return A string that describe the state of the chessboard
*/
FString AChessBoard::GetChessboardStateString()
{
	FString State = "";
	for (int32 i = 0; i < GetGameField()->Size; i++) {
		for (int32 j = 0; j < GetGameField()->Size; j++)
		{
			if (GetGameField()->GetTileBYXYPosition(i, j)->GetOnPiece() != nullptr)
			{
				State = State + GetGameField()->GetTileBYXYPosition(i, j)->ToString();
				if (GetGameField()->GetTileBYXYPosition(i, j)->GetOnPiece()->GetColor() == EPieceColor::BLACK)
					State = State + "b";
				else State = State + "w";
				State = State + GetGameField()->GetTileBYXYPosition(i, j)->GetOnPiece()->ToString();
			}
			else State = State + "-";
		}
	}
	return State;
}




/*
* @brief Method called when the game start or when spawned that spawn all the components of the chessboard
*
*/
void AChessBoard::BeginPlay()
{
	Super::BeginPlay();
	SpawnGameField();
	SpawnWhitePieces();
	SpawnBlackPieces();
}


