// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

//Forward declaration of the APiece class
class APiece;

/**
 * @brief Struct to keep a couple of tiles together, used in the array of moves to keep the tile that are involved in the move
 *
 */
USTRUCT()
struct FCoupleTile 
{
	GENERATED_BODY()

public:
	/**
	 * @brief pointer to the first tile of the couple (the order is important)
	*/	
	ATile* Tile1;
	/**
	* @brief pointer to the second tile of the couple (the order is important)
	*/

	ATile* Tile2;
	/**
	* @brief struct constructor keeped default
	*/

	FCoupleTile() = default;

	/**
	* @brief definition of the == operator for this struct
	*/
	bool operator==(const FCoupleTile& Other) const
	{
		return (Tile1 == Other.Tile1 && Tile2 == Other.Tile2);
	}
};

/**
 * @brief Enumeration to keep track of the status of the tiles
*/
UENUM()
enum class ETileStatus : uint8
{
	EMPTY		UMETA(DisplayName = "Empty"),
	OCCUPIED	UMETA(DisplayName = "Occupied"),
	SELECTABLE	UMETA(DisplayName = "Selectable"),
	EATABLE		UMETA(DisplayName = "Eatable")
};

/**
 * @brief Enumeration to keep track of the owner of the tile
*/
UENUM()
enum class ETileOwner : uint8
{
	BLACK	UMETA(DisplayName = "Black"),
	WHITE	UMETA(DisplayName = "White"),
	NONE	UMETA(DisplayName = "None"),
};


/**
 * @brief Clsss to implement the tile that inherit from the AActor unreal class
*/
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

	//Method to obtain the string that rapresent this tile in the move notation
	FString ToString();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/**
	* @brief reference to the scene component
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
		USceneComponent* Scene;
	/**
	* @brief reference to Mesh Component
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
		UStaticMeshComponent* StaticMeshComponent;
	/**
	* @brief status of the tile
	*/
		ETileStatus Status;
	/**
	* @brief Tile grid position
	*/
		FVector2D TileGridPosition;
	/**
	* @brief Tile owner 
	*/
		ETileOwner TileOwner;

	/**
	* @brief Array of materials
	* @details [0]->normal tile, [1]->Selectable tile, [2]->selectable and occupied tile
	*/
	UPROPERTY(EditAnywhere);
	TArray<UMaterial*> MaterialArray;
	/**
	* @brief reference to the piece on the tile (nullptr if there isn't)
	*/
		APiece* OnPiece;
};


/**
 * @brief Class to implement the white tile that inherit from the ATile class
 * @see ATile
*/
UCLASS()
class CHESS_API ATileWhite : public ATile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATileWhite();

protected:

};

/**
 * @brief Class to implement the white tile that inherit from the ATile class
 * @see ATile
*/
UCLASS()
class CHESS_API ATileBlack : public ATile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATileBlack();

protected:
};
