// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece.h"

APiece::APiece()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);

	this->SetGridPosition(0, 0);

}

void APiece::SetGridPosition(const double x, const double y)
{
	PieceGridPosition.Set(x, y);
}

FVector2D APiece::GetGridPosition()
{
	return PieceGridPosition;
}

TArray<FVector2D> APiece::Moves()
{
	return TArray<FVector2D>();
}

TArray<ATile*> APiece::AvaibleMoves(AGameField* GameField)
{
	return TArray<ATile*>();
}


void APiece::Move(ATile* Tile,AGameField* GameField)
{
	ATile* CurrTile = GameField->GetTileBYXYPosition(PieceGridPosition.X, PieceGridPosition.Y);
	CurrTile->SetOnPiece(nullptr);
	FVector ToLocation = AGameField::GetRelativeLocationByXYPosition(Tile->GetGridPosition().X, Tile->GetGridPosition().Y);
	this->SetActorLocation(ToLocation);
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

APiece* APiece::GetPiece()
{
	return this;
}

// Called when the game starts or when spawned
void APiece::BeginPlay()
{
	Super::BeginPlay();
}



