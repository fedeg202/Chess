// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessBoard.h"
#include "Chess_PlayerController.h"

// Sets default values
AChessBoard::AChessBoard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WhitePieces.SetNum(0);
	EatenWhitePieces.SetNum(0);

	BlackPieces.SetNum(0);
	EatenBlackPieces.SetNum(0);

}

TArray<APiece*>& AChessBoard::GetWhitePieces()
{
	return WhitePieces;
}

TArray<APiece*>& AChessBoard::GetEatenWhitePieces()
{
	return EatenWhitePieces;
}

TArray<APiece*>& AChessBoard::GetBlackPieces()
{
	return BlackPieces;
}

TArray<APiece*>& AChessBoard::GetEatenBlackPieces()
{
	return EatenBlackPieces;
}

AGameField* AChessBoard::GetGameField()
{
	return GameField;
}

void AChessBoard::SpawnGameField()
{
	FVector Location(0, 0, 0);
	GameField = GetWorld()->SpawnActor<AGameField>(GameFieldClass, Location, FRotator::ZeroRotator);
}

void AChessBoard::SpawnWhitePieces()
{
	int32 x = 1;
	int32 y = 0;
	APiece* Obj;
	FVector Location;
	for (y = 0; y < GameField->Size; y++)
	{
		Location = GameField->GetRelativeLocationByXYPosition(x, y);
		Obj = GetWorld()->SpawnActor<AWhitePawn>(WhitePawnClass, Location, FRotator::ZeroRotator);
		Obj->SetGridPosition(x, y);
		GameField->GetTileBYXYPosition(x,y)->SetTileStatus(ETileStatus::OCCUPIED);
		GameField->GetTileBYXYPosition(x,y)->SetTileOwner(ETileOwner::WHITE);
		GameField->GetTileBYXYPosition(x,y)->SetOnPiece(Obj);
		WhitePieces.Add(Obj);
	}
	x--;


	y = 0;
	Location = GameField->GetRelativeLocationByXYPosition(x, y);
	Obj = GetWorld()->SpawnActor<AWhiteRook>(WhiteRookClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x,y)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x,y)->SetTileOwner(ETileOwner::WHITE);
	GameField->GetTileBYXYPosition(x,y)->SetOnPiece(Obj);
	WhitePieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size - y - 1);
	Obj = GetWorld()->SpawnActor<AWhiteRook>(WhiteRookClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetTileOwner(ETileOwner::WHITE);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetOnPiece(Obj);
	WhitePieces.Add(Obj);


	y = 1;
	Location = GameField->GetRelativeLocationByXYPosition(x, y);
	Obj = GetWorld()->SpawnActor<AWhiteKnight>(WhiteKnightClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x,y)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x,y)->SetTileOwner(ETileOwner::WHITE);
	GameField->GetTileBYXYPosition(x,y)->SetOnPiece(Obj);
	WhitePieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size - y - 1);
	Obj = GetWorld()->SpawnActor<AWhiteKnight>(WhiteKnightClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetTileOwner(ETileOwner::WHITE);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetOnPiece(Obj);
	WhitePieces.Add(Obj);

	y = 2;
	Location = GameField->GetRelativeLocationByXYPosition(x, y);
	Obj = GetWorld()->SpawnActor<AWhiteBishop>(WhiteBishopClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x,y)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x,y)->SetTileOwner(ETileOwner::WHITE);
	GameField->GetTileBYXYPosition(x,y)->SetOnPiece(Obj);
	WhitePieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size - y - 1);
	Obj = GetWorld()->SpawnActor<AWhiteBishop>(WhiteBishopClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetTileOwner(ETileOwner::WHITE);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetOnPiece(Obj);
	WhitePieces.Add(Obj);

	y = 3;
	Location = GameField->GetRelativeLocationByXYPosition(x, y);
	Obj = GetWorld()->SpawnActor<AWhiteQueen>(WhiteQueenClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x, y)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x, y)->SetTileOwner(ETileOwner::WHITE);
	GameField->GetTileBYXYPosition(x, y)->SetOnPiece(Obj);
	WhitePieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size - y - 1);
	Obj = GetWorld()->SpawnActor<AWhiteKing>(WhiteKingClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x, GameField->Size - y - 1)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x, GameField->Size - y - 1)->SetTileOwner(ETileOwner::WHITE);
	GameField->GetTileBYXYPosition(x, GameField->Size - y - 1)->SetOnPiece(Obj);
	WhitePieces.Add(Obj);


}

void AChessBoard::SpawnBlackPieces()
{
	int32 x = GameField->Size - 2;
	int32 y = 0;
	APiece* Obj;
	FVector Location;
	for (y = 0; y < GameField->Size; y++)
	{
		Location = GameField->GetRelativeLocationByXYPosition(x, y);
		Obj = GetWorld()->SpawnActor<ABlackPawn>(BlackPawnClass, Location, FRotator::ZeroRotator);
		Obj->SetGridPosition(x, y);
		GameField->GetTileBYXYPosition(x,y)->SetTileStatus(ETileStatus::OCCUPIED);
		GameField->GetTileBYXYPosition(x,y)->SetTileOwner(ETileOwner::BLACK);
		GameField->GetTileBYXYPosition(x,y)->SetOnPiece(Obj);
		BlackPieces.Add(Obj);
	}
	x++;

	y = 0;
	Location = GameField->GetRelativeLocationByXYPosition(x, y);
	Obj = GetWorld()->SpawnActor<ABlackRook>(BlackRookClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x,y)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x,y)->SetTileOwner(ETileOwner::BLACK);
	GameField->GetTileBYXYPosition(x,y)->SetOnPiece(Obj);
	BlackPieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size- y - 1);
	Obj = GetWorld()->SpawnActor<ABlackRook>(BlackRookClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetTileOwner(ETileOwner::BLACK);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetOnPiece(Obj);
	BlackPieces.Add(Obj);


	y = 1;
	Location = GameField->GetRelativeLocationByXYPosition(x, y);
	Obj = GetWorld()->SpawnActor<ABlackKnight>(BlackKnightClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x,y)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x,y)->SetTileOwner(ETileOwner::BLACK);
	GameField->GetTileBYXYPosition(x,y)->SetOnPiece(Obj);
	BlackPieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size - y - 1);
	Obj = GetWorld()->SpawnActor<ABlackKnight>(BlackKnightClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetTileOwner(ETileOwner::BLACK);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetOnPiece(Obj);
	BlackPieces.Add(Obj);

	
	y = 2;
	Location = GameField->GetRelativeLocationByXYPosition(x, y);
	Obj = GetWorld()->SpawnActor<ABlackBishop>(BlackBishopClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x,y)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x,y)->SetTileOwner(ETileOwner::BLACK);
	GameField->GetTileBYXYPosition(x,y)->SetOnPiece(Obj);
	BlackPieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size - y - 1);
	Obj = GetWorld()->SpawnActor<ABlackBishop>(BlackBishopClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetTileOwner(ETileOwner::BLACK);
	GameField->GetTileBYXYPosition(x,GameField->Size - y - 1)->SetOnPiece(Obj);
	BlackPieces.Add(Obj);


	y = 3;
	Location = GameField->GetRelativeLocationByXYPosition(x, y);
	Obj = GetWorld()->SpawnActor<ABlackQueen>(BlackQueenClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, y);
	GameField->GetTileBYXYPosition(x, y)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x, y)->SetTileOwner(ETileOwner::BLACK);
	GameField->GetTileBYXYPosition(x, y)->SetOnPiece(Obj);
	BlackPieces.Add(Obj);

	Location = GameField->GetRelativeLocationByXYPosition(x, GameField->Size - y - 1);
	Obj = GetWorld()->SpawnActor<ABlackKing>(BlackKingClass, Location, FRotator::ZeroRotator);
	Obj->SetGridPosition(x, GameField->Size - y - 1);
	GameField->GetTileBYXYPosition(x, GameField->Size - y - 1)->SetTileStatus(ETileStatus::OCCUPIED);
	GameField->GetTileBYXYPosition(x, GameField->Size - y - 1)->SetTileOwner(ETileOwner::BLACK);
	GameField->GetTileBYXYPosition(x, GameField->Size - y - 1)->SetOnPiece(Obj);
	BlackPieces.Add(Obj);

}

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

void AChessBoard::AddWhiteEatenPiece(APiece* EatenPiece)
{
	if (EatenWhitePieces.IsEmpty())
		EatenWhitePieces.Add(EatenPiece);
	else 
	{
		EatenWhitePieces.Top()->SetActorHiddenInGame(true);
		EatenWhitePieces.Add(EatenPiece);
	}
}

void AChessBoard::AddBlackEatenPiece(APiece* EatenPiece)
{
	if (EatenBlackPieces.IsEmpty())
		EatenBlackPieces.Add(EatenPiece);
	else
	{
		EatenBlackPieces.Top()->SetActorHiddenInGame(true);
		EatenBlackPieces.Add(EatenPiece);
	}
}

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

bool AChessBoard::CheckOnCheck(ETileOwner SameColor, TArray<FCoupleTile> Moves)
{
	for (int32 i = 0; i < Moves.Num(); i++)
	{
		if (Moves[i].Tile2->GetOnPiece() != nullptr
			&& Moves[i].Tile2->GetOnPiece()->GetName() == EPieceName::KING)
			return true;
	}
	return false;
}

bool AChessBoard::CheckOnCheckmate(ETileOwner SameColor)
{
	return CheckOnCheck(SameColor) && CheckOnStalemate(SameColor);
}

bool AChessBoard::CheckOnStalemate(ETileOwner SameColor)
{
	if (SameColor == ETileOwner::BLACK)
		if (AllBlackSelectableMoves.Num() == 0) return true;
		else return false;
	else
		if (AllWhiteSelectableMoves.Num() == 0) return true;
		else return false;
}

APiece* AChessBoard::VirtualMove(FCoupleTile Tiles)
{
	APiece* OldOnPiece = Tiles.Tile2->GetOnPiece();
	Tiles.Tile2->SetTileStatus(Tiles.Tile1->GetTileStatus());
	Tiles.Tile2->SetTileOwner(Tiles.Tile1->GetTileOwner());
	Tiles.Tile2->SetOnPiece(Tiles.Tile1->GetOnPiece());

	Tiles.Tile1->SetTileStatus(ETileStatus::EMPTY);
	Tiles.Tile1->SetTileOwner(ETileOwner::NONE);
	Tiles.Tile1->SetOnPiece(nullptr);

	return OldOnPiece;
}

void AChessBoard::VirtualUnMove(FCoupleTile Tiles, APiece* OldOnPiece)
{
	ETileStatus Status;
	ETileOwner TileOwner;

	Tiles.Tile1->SetTileStatus(Tiles.Tile2->GetTileStatus());
	Tiles.Tile1->SetTileOwner(Tiles.Tile2->GetTileOwner());
	Tiles.Tile1->SetOnPiece(Tiles.Tile2->GetOnPiece());

	if (OldOnPiece != nullptr)
	{
		Status = ETileStatus::OCCUPIED;
		if (OldOnPiece->GetColor() == EPieceColor::BLACK) TileOwner = ETileOwner::BLACK;
		else TileOwner = ETileOwner::WHITE;
	}
	else {
		Status = ETileStatus::EMPTY;
		TileOwner = ETileOwner::NONE;
	}

	Tiles.Tile2->SetTileStatus(Status);
	Tiles.Tile2->SetTileOwner(TileOwner);
	Tiles.Tile2->SetOnPiece(OldOnPiece);
}

void AChessBoard::UpdateAllMoveBYColor(ETileOwner Color)
{
	TArray<APiece*> ColorPieces;
	TArray<FCoupleTile> AllColorSelectableMoves;
	TArray<FCoupleTile> AllColorMoves;
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
			tmp_piece = VirtualMove(CoupleTile_tmp);
			AllColorMoves = GetAllMovesByColor(OppositeColor);
			if (CheckOnCheck(Color,AllColorMoves))
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

TArray<FCoupleTile> AChessBoard::GetAllSelectableMovesByColor(ETileOwner SameColor)
{
	if (SameColor == ETileOwner::BLACK)
		return AllBlackSelectableMoves;
	else return AllWhiteSelectableMoves;
}

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

	SpawnBlackPieces();
	SpawnWhitePieces();

}

bool AChessBoard::CheckPawnPromotion(APiece* Piece)
{
	return Piece->GetName() == EPieceName::PAWN && ((Piece->GetColor() == EPieceColor::WHITE && Piece->GetGridPosition().X == GetGameField()->Size - 1) || (Piece->GetColor() == EPieceColor::BLACK && Piece->GetGridPosition().X == 0));
}



// Called when the game starts or when spawned
void AChessBoard::BeginPlay()
{
	Super::BeginPlay();
	SpawnGameField();
	SpawnWhitePieces();
	SpawnBlackPieces();

}


