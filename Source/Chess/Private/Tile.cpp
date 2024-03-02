// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Piece.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);

	Status = ETileStatus::EMPTY;
	TileGridPosition = FVector2D(0, 0);
	TileOwner = ETileOwner::NONE;

	MaterialArray.SetNum(3);

	OnPiece = nullptr);


}

ETileStatus ATile::GetTileStatus()
{
	return Status;
}

void ATile::SetTileStatus(ETileStatus S)
{
	Status = S;
}

void ATile::SetGridPosition(const double x, const double y)
{
	TileGridPosition.Set(x, y);
}

FVector2D ATile::GetGridPosition()
{
	return TileGridPosition;
}

ETileOwner ATile::GetTileOwner()
{
	return TileOwner;
}

void ATile::SetTileOwner(ETileOwner O)
{
	TileOwner = O;
}

void ATile::SetTileMaterial(int32 index)
{
	StaticMeshComponent->SetMaterial(0, MaterialArray[index]);
}

APiece* ATile::GetOnPiece()
{
	return OnPiece;
}

void ATile::SetOnPiece(APiece* Piece)
{
	OnPiece = Piece;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

ATileWhite::ATileWhite():ATile()
{}

ATileBlack::ATileBlack():ATile()
{}
