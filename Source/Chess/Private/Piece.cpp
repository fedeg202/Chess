// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece.h"
#include "ChessBoard.h"

APiece::APiece()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);

	PieceGridPosition.Set(0, 0);

}

void APiece::SetGridPosition(const double x, const double y)
{
	PieceGridPosition.Set(x, y);
}

void APiece::SetGridPosition(FVector2D GridPosition)
{
	PieceGridPosition = GridPosition;
}

FVector2D APiece::GetGridPosition()
{
	return PieceGridPosition;
}

TArray<FVector2D> APiece::Moves()
{
	return TArray<FVector2D>();
}

void APiece::Eat(ATile* EatTile, AChessBoard* ChessBoard)
{
	ATile* CurrTile = ChessBoard->GetGameField()->GetTileBYXYPosition(PieceGridPosition.X, PieceGridPosition.Y);

	FVector EatenLocation;
	if (CurrTile->GetTileOwner() == ETileOwner::BLACK)
		EatenLocation = AGameField::GetRelativeLocationByXYPosition(3, 9);
	else EatenLocation = AGameField::GetRelativeLocationByXYPosition(4, 9);

	APiece* EatenPiece = EatTile->GetOnPiece();
	EatenPiece->SetActorLocation(EatenLocation + ZPosition);

	if (CurrTile->GetTileOwner() == ETileOwner::BLACK) 
	{
		ChessBoard->GetWhitePieces().Remove(EatenPiece);
		ChessBoard->AddWhiteEatenPiece(EatenPiece);
	}
	else 
	{ 
		ChessBoard->GetBlackPieces().Remove(EatenPiece);
		ChessBoard->AddBlackEatenPiece(EatenPiece);
	}
	

	this->Move(EatTile, ChessBoard->GetGameField());
}

TArray<ATile*> APiece::AvaibleMoves(AChessBoard* ChessBoard)
{
	return TArray<ATile*>();
}


void APiece::Move(ATile* Tile,AGameField* GameField)
{
	ATile* CurrTile = GameField->GetTileBYXYPosition(PieceGridPosition.X, PieceGridPosition.Y);
	CurrTile->SetOnPiece(nullptr);
	FVector ToLocation = AGameField::GetRelativeLocationByXYPosition(Tile->GetGridPosition().X, Tile->GetGridPosition().Y);
	this->SetActorLocation(ToLocation + ZPosition);
	Tile->SetOnPiece(this);
	this->SetGridPosition(Tile->GetGridPosition().X, Tile->GetGridPosition().Y);
	if (CurrTile->GetTileOwner() == ETileOwner::WHITE)
	{
		Tile->SetTileOwner(ETileOwner::WHITE);
	}
	else if (CurrTile->GetTileOwner() == ETileOwner::BLACK)
	{
		Tile->SetTileOwner(ETileOwner::BLACK);
	}
	Tile->SetTileStatus(ETileStatus::OCCUPIED);
	CurrTile->SetTileOwner(ETileOwner::NONE);
	CurrTile->SetTileStatus(ETileStatus::EMPTY);

}


EPieceColor APiece::GetColor()
{
	return Color;
}

EPieceName APiece::GetName()
{
	return Name;
}

FString APiece::ToString()
{
	return FString();
}

int32 APiece::GetValue()
{
	return Value;
}

void APiece::ShowSelected()
{
	StaticMeshComponent->SetMaterial(0, SelectedMaterial);
}

void APiece::UnshowSelected()
{
	StaticMeshComponent->SetMaterial(0, BaseMaterial);
}

// Called when the game starts or when spawned
void APiece::BeginPlay()
{
	Super::BeginPlay();
}



