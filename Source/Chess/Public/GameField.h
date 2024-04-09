// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Tile.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameField.generated.h"


/*
* @brief Class to implement the gamefield made of all the tiles
*/

UCLASS()
class CHESS_API AGameField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameField();
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Size of the tiles
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	int32 TileSize = 100;

	//Number of tile for every side of the board
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Size;

	//Tile class
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<ATile> TileClass;
	//Black tile class
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<ATileBlack> TileBlackClass;
	//White tile class
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<ATileWhite> TileWhiteClass;

	//Method to spawn all the tiles of the board
	void GenerateField();
	//Method to bring all the tile to their starting status
	void ResetField();
	
	//Static method to get the vector with the 3D location of the center of the tile from his coordinates(x,y)
	static FVector GetRelativeLocationByXYPosition(const int32 inX, const int32 inY);
	//Return a pointer to the tile that is in position (x,y) in the tile matrix
	ATile* GetTileBYXYPosition(const int32 x, const int32 y);

	//Return true if x and y are in the size of the gamefield else return false
	bool IsInRange(const int32 x, const int32 y);
	//Return true the position is in the size of the gamefield else return false
	bool IsInRange(FVector2D Position);

protected:
	//Method to initialize the matrix of the tiles
	TArray<TArray<ATile*>> TileMatrixInit(int32 Size);
	//Tiles matrix
	TArray<TArray<ATile*>> TileMatrix;
};
