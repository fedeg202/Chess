// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class APiece;


USTRUCT()
struct FCoupleTile 
{
	GENERATED_BODY()

public:
	ATile* Tile1;
	ATile* Tile2;

	FCoupleTile() = default;

	bool operator==(const FCoupleTile& Other) const
	{
		return (Tile1 == Other.Tile1 && Tile2 == Other.Tile2);
	}
};

UENUM()
enum class ETileStatus : uint8
{
	EMPTY		UMETA(DisplayName = "Empty"),
	OCCUPIED	UMETA(DisplayName = "Occupied"),
	SELECTABLE	UMETA(DisplayName = "Selectable"),
	EATABLE		UMETA(DisplayName = "Eatable")
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

	//Get the tile status
	ETileStatus GetTileStatus();
	//Set the tile status
	void SetTileStatus(ETileStatus S);

	// set the tile grid position
	void SetGridPosition(const double x, const double y);
	//return the tile grid position
	FVector2D GetGridPosition();

	//return the tile color owner
	ETileOwner GetTileOwner();
	//set the tile color owner
	void SetTileOwner(ETileOwner O);

	//Set the tile material from the array of materials (different material for the avaible tiles when moving a piece)
	void SetTileMaterial(int32 index);

	//return the pointer at the piece on the tile
	APiece* GetOnPiece();
	//set the pointer to the piece on the tile
	void SetOnPiece(APiece* Piece);

	//Method to set Status, Owner and On Piece
	void SetStatusAndOwnerAndOnPiece(ETileStatus S, ETileOwner O, APiece* Piece);

	//Methot to restore the tile to is starting state
	void ResetTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
		//reference to a Scene componenent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
		USceneComponent* Scene;
		//refrence to a mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
		UStaticMeshComponent* StaticMeshComponent;
		// status of the tile
		ETileStatus Status;
		//grid position fo the tile
		FVector2D TileGridPosition;
		//color owner of the tile
		ETileOwner TileOwner;

		//reference to a array of material, 0 -> standard tile, 1->selectable tile, 2-> selectable occupied tile
	UPROPERTY(EditAnywhere);
		TArray<UMaterial*> MaterialArray;
		// reference to the piece on the tile
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
};
