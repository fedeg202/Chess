// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Tile.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameField.generated.h"


UCLASS()
class CHESS_API AGameField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameField();
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	int32 TileSize = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Size;

	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<ATile> TileClass;

	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<ATileBlack> TileBlackClass;

	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<ATileWhite> TileWhiteClass;

	void GenerateField();

	static FVector GetRelativeLocationByXYPosition(const int32 inX, const int32 inY);
	ATile* GetTileBYXYPosition(const int32 x, const int32 y);

protected:

	TArray<TArray<ATile*>> TileMapArrayInit(int32 Size);
	TArray<TArray<ATile*>> TileMatrix;
};
