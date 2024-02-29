// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameField.h"
#include "ChessPawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"

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
	TSubclassOf<AWhitePawn> WhitePawnClass;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<AWhiteKnight> WhiteKnightClass;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<AWhiteRook> WhiteRookClass;
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<AWhiteBishop> WhiteBishopClass;

	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<AGameField> GameFieldClass;

	TArray<APiece*>& GetWhitePieces();
	TArray<APiece*>& GetBlackPieces();

	AGameField* GetGameField();

	void SpawnGameField();
	void SpawnWhitePieces();
	void SpawnBlackPieces();

	void ShowSelectableTiles(TArray<ATile*>& SelectableTiles);
	void UnShowSelectableTiles(TArray<ATile*>& SelectableTiles);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	TArray<APiece*> WhitePieces;
	TArray<APiece*> BlackPieces;

	AGameField* GameField;


};
