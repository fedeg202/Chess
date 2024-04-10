// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Piece.h"

/**
 * @brief ATile class constructor
 * 
*/
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

	OnPiece = nullptr;


}

/**
 * @brief Getter for the tile status
 *
 * @return Status of the tile as a ETileStatus
*/
ETileStatus ATile::GetTileStatus()
{
	return Status;
}

/**
 * @brief Setter for the tile status
 *
 * @param S status of the tile that you want to set as a ETileStatus
*/
void ATile::SetTileStatus(ETileStatus S)
{
	Status = S;
}

/**
 * @brief Setter for the grid position
 *
 * @param x the x coordinate
 * @param y the y coordinate
*/
void ATile::SetGridPosition(const double x, const double y)
{
	TileGridPosition.Set(x, y);
}

/**
 * @brief Getter for the grid position
 *
 * @return a 2D vector with the grid position
*/
FVector2D ATile::GetGridPosition()
{
	return TileGridPosition;
}

/**
 * @brief Getter for the tile owner
 *
 * @return Owner of the tile as a ETileOwner
*/
ETileOwner ATile::GetTileOwner()
{
	return TileOwner;
}

/**
 * @brief Setter for the tile owner
 *
 * @param O owner of the tile that you want to set as a ETileOwner
*/
void ATile::SetTileOwner(ETileOwner O)
{
	TileOwner = O;
}

/**
 * @brief Method to change the tile material based on the different situations
 * @see MaterialArray
 *
 * @param index index of the material in the material array
*/
void ATile::SetTileMaterial(int32 index)
{
	StaticMeshComponent->SetMaterial(0, MaterialArray[index]);
}

/**
 * @brief Getter for the piece on the tile
 *
 * @return pointer to the piece on the tile
*/
APiece* ATile::GetOnPiece()
{
	return OnPiece;
}

/**
 * @brief Setter for the piece on the tile
 *
 * @param Piece pointer to the piece that you want to set on the tile
*/
void ATile::SetOnPiece(APiece* Piece)
{
	OnPiece = Piece;
}

/**
 * @brief Setter for some attribute of the Tile: Status, Owner & OnPiece
 * @see SetTileStatus()
 * @see SetTileOwner()
 * @see SetOnPiece()
 *
 *
 * @param Piece pointer to the piece that you want to set on the tile
*/
void ATile::SetStatusAndOwnerAndOnPiece(ETileStatus S, ETileOwner O, APiece* Piece)
{
	SetTileStatus(S);
	SetTileOwner(O);
	SetOnPiece(Piece);
}

/**
 * @brief Method to reset the tile to its starting state
 *
*/
void ATile::ResetTile()
{
	SetStatusAndOwnerAndOnPiece(ETileStatus::EMPTY, ETileOwner::NONE, nullptr);
	SetTileMaterial(0);
}

/**
 * @brief Method to obtain the string of two char that indentify this tile in the Long Algebraic Chess notation
 *
*/
FString ATile::ToString()
{
	char Letter;
	Letter = static_cast<char>(97 + TileGridPosition.Y);
	FString Result = FString::Printf(TEXT("%c%s"), Letter, *FString::FromInt(TileGridPosition.X+1));
	return Result;
}

/**
 * @brief Called at the start of the game or when spawned
 *
*/
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

/**
 * @brief ATileWhite class constructor
 * @see ATile()
*/
ATileWhite::ATileWhite():ATile()
{}

/**
 * @brief ATileBlack class constructor
 * @see ATile() 
*/
ATileBlack::ATileBlack():ATile()
{}
