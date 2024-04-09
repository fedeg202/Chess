// Fill out your copyright notice in the Description page of Project Settings.


#include "GameField.h"

/**
 * @brief AGameField class constructor
 *
 */
AGameField::AGameField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Size = 8;


	TileMatrix = TileMatrixInit(Size);

}

/**
 * @brief Called when the game starts or when spawned, generate the game field
 *
 */
void AGameField::BeginPlay()
{
	Super::BeginPlay();
	GenerateField();
	
}

/**
 * @brief Method to create the game field with alle the tiles
 *
 */
void AGameField::GenerateField()
{
	int32 phase = 0;
	for (int32 x = 0; x < Size; x++) 
	{
		for (int32 y = 0; y < Size; y++)
		{
			FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
			ATile* Obj;
			if ((y + phase) % 2 == 0)
			{
				Obj = GetWorld()->SpawnActor<ATileBlack>(TileBlackClass, Location, FRotator::ZeroRotator);
			}
			else
			{
				Obj = GetWorld()->SpawnActor<ATileWhite>(TileWhiteClass, Location, FRotator::ZeroRotator);
			}
			Obj->SetGridPosition(x, y);
			TileMatrix[x][y] = Obj;
		}
		phase++;
	}
}

/**
 * @brief Method to reset the game field to its starting state
 *
 */
void AGameField::ResetField()
{
	if (!TileMatrix.IsEmpty())
		for (int32 i = 0; i < Size; i++) 
		{
			for (int32 j = 0;j<Size;j++)
			{
				TileMatrix[i][j]->ResetTile();
			}
		}
}


/**
 * @brief Static method to obtain the relative position from the x and y coordinates
 * 
 * @param inX the x coordinate
 * @param inY the y coordinate
 * @return A 3D vector with the relative position
 */
FVector AGameField::GetRelativeLocationByXYPosition(const int32 inX, const int32 inY)
{	
	return 100 * FVector(inX,inY,0);
}

/**
 * @brief Method to obtain a tile by his x and y "grid position"
 * 
 * @param x the x coordinate of the tile in the grid
 * @param y the y coordinate of the tile in the grid
 * @return a pointer to the tile that correspond to the coordinates in the parameters
 */
ATile* AGameField::GetTileBYXYPosition(const int32 x, const int32 y)
{
	if (x >= 0 && x < Size && y >= 0 && y < Size)
		return TileMatrix[x][y];
	else return nullptr;
}
/**
 * @brief Method to check if the coordinates are in the range of the field
 *
 * @param x the x coordinate
 * @param y the y coordinate
 * @return true if is in range, false otherwise
 */
bool AGameField::IsInRange(const int32 x, const int32 y)
{
	return x < Size && x >= 0 && y < Size && y >= 0;
}
/**
 * @brief Method to check if the coordinates are in the range of the field
 *
 * @param Position a 2D vector with the coordinates
 * @return true if is in range, false otherwise
 */
bool AGameField::IsInRange(FVector2D Position)
{
	return Position.X < Size && Position.X >= 0 && Position.Y < Size && Position.Y >= 0;
}

/**
 * @brief Method to initialise the Matrix of the tiles
 *
 * @param ArrSize number of tile for every side of the square of the field
 * @return Matrix of pointer to tile
 */
TArray<TArray<ATile*>> AGameField::TileMatrixInit(int32 ArrSize)
{
	TArray<TArray<ATile*>> TileArrOfArr;
	TileArrOfArr.SetNum(ArrSize);

	for (int32 RowIndex = 0; RowIndex < ArrSize; ++RowIndex)
	{
		TileArrOfArr[RowIndex].SetNum(ArrSize);
	}
	return TileArrOfArr;
}


