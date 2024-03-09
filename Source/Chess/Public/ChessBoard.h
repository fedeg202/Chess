// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameField.h"
#include "ChessPawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessBoard.generated.h"

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

	TArray<APiece*>& GetWhitePieces();
	TArray<APiece*>& GetEatenWhitePieces();

	TArray<APiece*>& GetBlackPieces();
	TArray<APiece*>& GetEatenBlackPieces();

	AGameField* GetGameField();

	void SpawnGameField();
	void SpawnWhitePieces();
	void SpawnBlackPieces();

	void ShowSelectableTiles(TArray<ATile*>& SelectableTiles);
	void UnShowSelectableTiles(TArray<ATile*>& SelectableTiles);

	void AddWhiteEatenPiece(APiece* EatenPiece);
	void AddBlackEatenPiece(APiece* EatenPiece);

	bool CheckOnCheck(ETileOwner SameColor);
	bool CheckOnCheck(ETileOwner SameColor, TArray<FCoupleTile> Moves);
	bool CheckOnCheckmate(ETileOwner SameColor);
	bool CheckOnStalemate(ETileOwner SameColor);

	APiece* VirtualMove(FCoupleTile Tiles);
	void VirtualUnMove(FCoupleTile Tiles, APiece* OlOnPiece);

	void UpdateAllMoveBYColor(ETileOwner Color);
	
	TArray<FCoupleTile> GetAllSelectableMovesByColor(ETileOwner SameColor);

	TArray<FCoupleTile> GetAllMovesByColor(ETileOwner SameColor);

	void ResetChessBoard();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	TArray<APiece*> WhitePieces;
	TArray<APiece*> EatenWhitePieces;
	TArray<FCoupleTile> AllWhiteSelectableMoves;

	TArray<APiece*> BlackPieces;
	TArray<APiece*> EatenBlackPieces;
	TArray<FCoupleTile> AllBlackSelectableMoves;

	AGameField* GameField;


};
