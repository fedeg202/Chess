// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameField.h"
class AChessBoard;

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Piece.generated.h"

/**
 * @brief Enum to handle the name of the pieces
 *
 */
UENUM()
enum class EPieceName : uint8
{
	PAWN		UMETA(DisplayName = "Pawn"),
	ROOK		UMETA(DisplayName = "Rook"),
	KNIGHT		UMETA(DisplayName = "Knight"),
	BISHOP		UMETA(DisplayName = "Bishop"),
	QUEEN		UMETA(DisplayName = "Queen"),
	KING		UMETA(DisplayName = "King"),
};

/**
 * @brief Enum to handle the color of the pieces
 *
 */
UENUM()
enum class EPieceColor : uint8
{
	WHITE		UMETA(DisplayName = "White"),
	BLACK		UMETA(DisplayName = "Black"),
};

/*
* @brief Class for Generic Chess Piece, that is the father class of all the chess pieces
*/

UCLASS()
class CHESS_API APiece : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APiece();
	// Set the grid position
	void SetGridPosition(const double x, const double y);
	void SetGridPosition(FVector2D GridPosition);
	//return a fvector with the grid position of the piece
	FVector2D GetGridPosition();
	//Virtual method to return all the moves as a 2D vector, that a generic queen can do freely
	virtual TArray<FVector2D> Moves();
	//Method to make the chess eat (or take) move
	void Eat(ATile* EatTile, AChessBoard* ChessBoard);
	//Virtual method to return a pointer to all the tiles where the white queen can go
	virtual TArray<ATile*> AvaibleMoves(AChessBoard* ChessBoard);
	//Method to move a piece to a Tile
	void Move(ATile* Tile, AGameField* GameField);

	//Return the color of the piece
	EPieceColor GetColor();
	//Return the name of the piece
	EPieceName GetName();

	//Return the correct char to describe the moves with the Long Algebric Notation
	virtual FString ToString();

	int32 GetValue();

	/*
	* @brief Reference to the material interface for the piece when is normal
	*/
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* BaseMaterial;

	/*
	* @brief Reference to the material interface for the piece when is selected
	*/
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* SelectedMaterial; 

	void ShowSelected();

	void UnshowSelected();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	* @brief Reference to a scene component
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
	USceneComponent* Scene;

	/*
	* @brief Reference to the static mesh component
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
	UStaticMeshComponent* StaticMeshComponent;

	/*
	* @brief Position of the piece in the grid
	*/
	FVector2D PieceGridPosition;

	/*
	* @brief Color of the piece
	*/
	EPieceColor Color;
	/*
	* @brief name of the piece
	*/
	EPieceName Name;

	/*
	* @brief Value of the piece
	*/
	int32 Value;

	/*
	* @brief ZOffset position to make the entire piece stay out of the tiles
	*/
	FVector ZPosition = FVector(0, 0, 10);
};
