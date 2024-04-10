// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece.h"
#include "ChessBoard.h"

/*
* @brief APiece class constructor
*/
APiece::APiece()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);

	PieceGridPosition.Set(0, 0);

}

/*
* @brief Setter for the grid position
* 
* @param x the x coordinate
* @param y the y coordinate
*/
void APiece::SetGridPosition(const double x, const double y)
{
	PieceGridPosition.Set(x, y);
}

/*
* @brief Setter for the grid position
*
* @param GridPosition the position as a 2D vector
*/
void APiece::SetGridPosition(FVector2D GridPosition)
{
	PieceGridPosition = GridPosition;
}

/*
* @brief Getter for the grid position
*
* @return the grid position as a 2D vector
*/
FVector2D APiece::GetGridPosition()
{
	return PieceGridPosition;
}

/*
* @brief Method to obtain the moves for the particular piece to be overrided by the child classes
*
*/
TArray<FVector2D> APiece::Moves()
{
	return TArray<FVector2D>();
}

/*
* @brief Method to implement the eat of capture of the pieces
* 
* @details Take the piece on the EatTile and put it outside of the chessboard and in the array of the right color eaten pieces, and then call the move to move the piece to the now empty tile
*
* @param EatTile the tile where you want to make the piece eat
* @param ChessBoard the chessboard where the piece is
*/
void APiece::Eat(ATile* EatTile, AChessBoard* ChessBoard)
{
	ATile* CurrTile = ChessBoard->GetGameField()->GetTileBYXYPosition(PieceGridPosition.X, PieceGridPosition.Y);

	FVector EatenLocation;
	if (CurrTile->GetTileOwner() == ETileOwner::BLACK)
		EatenLocation = AGameField::GetRelativeLocationByXYPosition(3, 9);
	else EatenLocation = AGameField::GetRelativeLocationByXYPosition(4, 9);

	APiece* EatenPiece = EatTile->GetOnPiece();
	EatenPiece->SetActorLocation(EatenLocation + ZPosition);

	if (CurrTile->GetTileOwner() == ETileOwner::BLACK) 
	{
		ChessBoard->GetWhitePieces().Remove(EatenPiece);
		ChessBoard->AddWhiteEatenPiece(EatenPiece);
	}
	else 
	{ 
		ChessBoard->GetBlackPieces().Remove(EatenPiece);
		ChessBoard->AddBlackEatenPiece(EatenPiece);
	}
	

	this->Move(EatTile, ChessBoard->GetGameField());
}

/*
* @brief Method to obtain the avaible moves for the particular piece to be overrided by the child classes
*
*/
TArray<ATile*> APiece::AvaibleMoves(AChessBoard* ChessBoard)
{
	return TArray<ATile*>();
}

/*
* @brief Method to implement the move of the pieces
*
* @details Take the two tiles involved, change the status and the owner to make them right after the move and relocate the piece actor to be in the right position after the move
*
* @param Tile the tile where you want to make the piece go
* @param GameField the gamefield on witch is the piece
*/
void APiece::Move(ATile* Tile,AGameField* GameField)
{
	ATile* CurrTile = GameField->GetTileBYXYPosition(PieceGridPosition.X, PieceGridPosition.Y);
	CurrTile->SetOnPiece(nullptr);
	FVector ToLocation = AGameField::GetRelativeLocationByXYPosition(Tile->GetGridPosition().X, Tile->GetGridPosition().Y);
	this->SetActorLocation(ToLocation + ZPosition);
	Tile->SetOnPiece(this);
	this->SetGridPosition(Tile->GetGridPosition().X, Tile->GetGridPosition().Y);
	if (CurrTile->GetTileOwner() == ETileOwner::WHITE)
	{
		Tile->SetTileOwner(ETileOwner::WHITE);
	}
	else if (CurrTile->GetTileOwner() == ETileOwner::BLACK)
	{
		Tile->SetTileOwner(ETileOwner::BLACK);
	}
	Tile->SetTileStatus(ETileStatus::OCCUPIED);
	CurrTile->SetTileOwner(ETileOwner::NONE);
	CurrTile->SetTileStatus(ETileStatus::EMPTY);

}

/*
* @brief Getter for the color of the piece
*
*/
EPieceColor APiece::GetColor()
{
	return Color;
}

/*
* @brief Getter for the name of the piece
*
*/
EPieceName APiece::GetName()
{
	return Name;
}

/**
 * @brief This method return the character that identify this piece in the chess notation
 *
 * @return FString with the character that identify this piece in chess notation
 */
FString APiece::ToString()
{
	return FString();
}

/**
 * @brief Getter for the value of the piece
 *
 */
int32 APiece::GetValue()
{
	return Value;
}

/**
 * @brief Method to show if the piece is the selected one by changing his material
 * @details Change the material to the "SelectedMaterial" to make it more visible and make easy to see what piece has been moved on the latest turn or on what piece
 *			the human player has clicked on
 *
 */
void APiece::ShowSelected()
{
	StaticMeshComponent->SetMaterial(0, SelectedMaterial);
}

/**
 * @brief Method to unshow if the piece is the selected one by rechanging his material
 * @see ShowSelected()
 *
 */
void APiece::UnshowSelected()
{
	StaticMeshComponent->SetMaterial(0, BaseMaterial);
}

/**
 * @brief Called at the start of the game or when spawned
 *
 */
void APiece::BeginPlay()
{
	Super::BeginPlay();
}



