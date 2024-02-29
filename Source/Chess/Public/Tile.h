// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class APiece;

UENUM()
enum class ETileStatus : uint8
{
	EMPTY	UMETA(DisplayName = "Empty"),
	OCCUPIED	UMETA(DisplayName = "Occupied"),
	SELECTABLE	UMETA(DisplayName = "Selectable")
};

UENUM()
enum class ETileOwner : uint8
{
	BLACK	UMETA(DisplayName = "Black"),
	WHITE	UMETA(DisplayName = "White"),
	NONE	UMETA(DisplayName = "None"),
};


UCLASS()
class CHESS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	ETileStatus GetTileStatus();
	void SetTileStatus(ETileStatus S);

	void SetGridPosition(const double x, const double y);

	FVector2D GetGridPosition();

	ETileOwner GetTileOwner();
	void SetTileOwner(ETileOwner O);

	void SetTileMaterial(int32 index);

	APiece* GetOnPiece();
	void SetOnPiece(APiece* Piece);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
		USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
		UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
		ETileStatus Status;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
		FVector2D TileGridPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
		ETileOwner TileOwner;

	UPROPERTY(EditAnywhere);
		TArray<UMaterial*> MaterialArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
		APiece* OnPiece;
};

UCLASS()
class CHESS_API ATileWhite : public ATile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATileWhite();

protected:

};

UCLASS()
class CHESS_API ATileBlack : public ATile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATileBlack();

protected:
	// Called when the game starts or when spawned
};
