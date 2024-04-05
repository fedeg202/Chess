// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameField.h"
#include "ChessPawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Chess_PlayerInterface.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessBoard.generated.h"



USTRUCT()
struct FMove
{
	GENERATED_BODY()

public:
	FMove() = default;
	FMove(FCoupleTile CTiles,EColor PlayerColor, bool bEat = false,bool bPawnPromotionFlag = false) 
	{
		Tiles = CTiles;
		Player = PlayerColor;
		bEatFlag = bEat;
		bPawnPromotion = bPawnPromotionFlag;
		PawnPromotedTo = EPieceName::PAWN;
	}
	FCoupleTile Tiles;
	EColor Player;
	bool bEatFlag;
	bool bPawnPromotion;
	EPieceName PawnPromotedTo;
};


/*
* Class to implement the complete Chessboard, tiles + pieces
*/

UCLASS()
class CHESS_API AChessBoard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChessBoard();

	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<ABlackPawn> BlackPawnClass;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<ABlackKnight> BlackKnightClass;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<ABlackRook> BlackRookClass;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<ABlackBishop> BlackBishopClass;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<ABlackQueen> BlackQueenClass;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<ABlackKing> BlackKingClass;

	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<AWhitePawn> WhitePawnClass;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<AWhiteKnight> WhiteKnightClass;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<AWhiteRook> WhiteRookClass;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<AWhiteBishop> WhiteBishopClass;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<AWhiteQueen> WhiteQueenClass;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<AWhiteKing> WhiteKingClass;

	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<AGameField> GameFieldClass;

	//Return the array of the white pieces
	TArray<APiece*>& GetWhitePieces();
	//Return the array of white eaten(or taken) pieces
	TArray<APiece*>& GetEatenWhitePieces();

	//Return the array of black pieces
	TArray<APiece*>& GetBlackPieces();
	//Return the array of black eaten(or taken) pieces
	TArray<APiece*>& GetEatenBlackPieces();

	TArray<APiece*>& GetPiecesByColor(ETileOwner SameColor);

	//Return the pointer to the gamefield
	AGameField* GetGameField();

	//Method to spawn the Gamefield
	void SpawnGameField();
	//Method to spawn all the white pieces
	void SpawnWhitePieces();
	//Method to spawn all the black pieces
	void SpawnBlackPieces();

	//Method to display the selectable tiles by the player by changing their material and their status
	void ShowSelectableTiles(TArray<ATile*>& SelectableTiles);
	//Method to undisplay the selectable tiles by the player by changing their material to the default one and bring the tile back to their prevous status
	void UnShowSelectableTiles(TArray<ATile*>& SelectableTiles);

	//Method to add an eaten piece to the array and make sure that only the last one eaten is visible
	void AddWhiteEatenPiece(APiece* EatenPiece);
	//Method to add an eaten piece to the array and make sure that only the last one eaten is visible
	void AddBlackEatenPiece(APiece* EatenPiece);

	//Method to remove an eaten piece from the array and make sure that the next one return visible
	APiece* PopWhiteEatenPiece();
	//Method to remove an eaten piece and make sure that the next one return visible
	APiece* PopBlackEatenPiece();

	//Method to check if the player with the color coded in ETileOwner, is in check
	bool CheckOnCheck(ETileOwner SameColor);
	//Method to check if the player with the color coded in ETileOwner, and with the opponent that has the moves passed as an argument is in check;
	bool CheckOnCheck(ETileOwner SameColor, TArray<FCoupleTile> Moves);
	//Method to check if the player with the color coded in ETileOwner, is in checkmate
	bool CheckOnCheckmate(ETileOwner SameColor);
	//Method to check if the player with the color coded in ETileOwner, is in stalemate
	bool CheckOnStalemate(ETileOwner SameColor);

	//Method to simulate moves without moving the pieces
	APiece* VirtualMove(FCoupleTile Tiles);
	//Method to reverse the effect of VirtualMove method
	void VirtualUnMove(FCoupleTile Tiles, APiece* OlOnPiece);

	//Method to update all the avaible moves of the player with the color coded in ETileOwner
	void UpdateAllMoveBYColor(ETileOwner Color);
	
	//Return all the Selectable moves of the player with the color coded in ETileOwner
	TArray<FCoupleTile>& GetAllSelectableMovesByColor(ETileOwner SameColor,bool bCopy = false);
	//Return all the moves (not only the selectable) of the player with the color coded in ETileOwner
	TArray<FCoupleTile> GetAllMovesByColor(ETileOwner SameColor);

	//Method to reset the chessboard to the starting position
	void ResetChessBoard();

	//Method to check if the piece is a pawn and is elegible for a pawn promotion
	bool CheckPawnPromotion(APiece* Piece);
	//Method to check if there is a pawn elegible for a pawn promotion of the given color player
	bool CheckPawnPromotion(ETileOwner Color);

	//Method to create the string that encode the move
	FString CreateMoveString(APiece* Piece, FCoupleTile Tiles,bool b_eatFlag = false,bool b_promotionFlag = false, bool b_checkFlag = false, bool b_checkmateFlag = false);

	//Method to add the move to the AllMoves array
	void AddMove(FMove Move);

	//Return the AllMoves array
	TArray<FMove>& GetAllMoves();

	//Method to restore the chessboard to a target index starting from a current index going forward (called only if the current index is more than the target one)
	void RestoreChessboardToMoveBackward(int32 CurrentMoveIndex,int32 TargetMoveindex);
	//Method to restore the chessboard to a target index starting from a current index going backward (Called only if the currrent index is less than the tagret one)
	void RestoreChessboardToMoveForward(int32 CurrentMoveindex, int32 TargetMoveIndex);

	//Method to obtain the last move added
	FMove& GetTopMove();

	//Method to remove all the move starting from a starting index
	void RemoveMovesFromStartingIndex(int32 StartingIndex);

	FString GetChessboardStateString();

	//Map to keep track of all the states and to implement the draw in case of three occurences of the same state
	TMap<FString, int32> StateOccurrences;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//Reference to an array of pointer to pieces with all the white pieces
	TArray<APiece*> WhitePieces;
	//Reference to an array of pointer to pieces with all the eaten white pieces
	TArray<APiece*> EatenWhitePieces;
	//Reference to an array CoupleTile with all the selectable moves by the white player
	TArray<FCoupleTile> AllWhiteSelectableMoves;


	//Reference to an array of pointer to pieces with all the black pieces
	TArray<APiece*> BlackPieces;
	//Reference to an array of pointer to pieces with all the eaten black pieces
	TArray<APiece*> EatenBlackPieces;
	//Reference to an array CoupleTile with all the selectable moves by the black player
	TArray<FCoupleTile> AllBlackSelectableMoves;

	//Refernce to a Gamefield object
	AGameField* GameField;

	//Reference to an array with all the moves
	TArray<FMove> AllMoves;

	
};
