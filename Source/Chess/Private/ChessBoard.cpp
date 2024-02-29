// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessBoard.h"

// Sets default values
AChessBoard::AChessBoard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WhitePieces.SetNum(16);
	BlackPieces.SetNum(16);

}

TArray<APiece*>& AChessBoard::GetWhitePieces()
{
	return WhitePieces;
}

TArray<APiece*>& AChessBoard::GetBlackPieces()
{
	return BlackPieces;
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
		Tile->SetTileMaterial(0);

	}
}

// Called when the game starts or when spawned
void AChessBoard::BeginPlay()
{
	Super::BeginPlay();
	SpawnGameField();
	SpawnWhitePieces();
	SpawnBlackPieces();

}


