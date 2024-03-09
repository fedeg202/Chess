// Fill out your copyright notice in the Description page of Project Settings.


#include "GameField.h"

// Sets default values
AGameField::AGameField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Size = 8;


	TileMatrix = TileMapArrayInit(Size);

}

// Called when the game starts or when spawned
void AGameField::BeginPlay()
{
	Super::BeginPlay();
	GenerateField();
	
}


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

void AGameField::ResetField()
{
	if (!TileMatrix.IsEmpty())
		for (int32 i = 0; i < Size; i++) 
		{
			for (int32 j = 0;j<Size;j++)
			{
				TileMatrix[i][j]->SetOnPiece(nullptr);
				TileMatrix[i][j]->SetTileOwner(ETileOwner::NONE);
				TileMatrix[i][j]->SetTileStatus(ETileStatus::EMPTY);
			}
		}
}



FVector AGameField::GetRelativeLocationByXYPosition(const int32 inX, const int32 inY)
{	
	return 100 * FVector(inX,inY,0);
}

ATile* AGameField::GetTileBYXYPosition(const int32 x, const int32 y)
{
	if (x >= 0 && x < Size && y >= 0 && y < Size)
		return TileMatrix[x][y];
	else return nullptr;
}


TArray<TArray<ATile*>> AGameField::TileMapArrayInit(int32 ArrSize)
{
	TArray<TArray<ATile*>> TileArrOfArr;
	TileArrOfArr.SetNum(ArrSize);

	for (int32 RowIndex = 0; RowIndex < ArrSize; ++RowIndex)
	{
		TileArrOfArr[RowIndex].SetNum(ArrSize);
	}
	return TileArrOfArr;
}


