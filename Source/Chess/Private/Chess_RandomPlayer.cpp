// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_RandomPlayer.h"
#include "ChessGameMode.h"

// Sets default values
AChess_RandomPlayer::AChess_RandomPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GameInstance = Cast<UChess_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PlayerNumber = -1;

	Color = EColor::NONE;

	SelectedPiece = nullptr;
	Piece_SelectableMoves.SetNum(0);
	All_SelectableMoves.SetNum(16);
}

// Called when the game starts or when spawned
void AChess_RandomPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChess_RandomPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChess_RandomPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AChess_RandomPlayer::OnTurn()
{
	IsMyTurn = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RandomPlayer Turn"));
	GameInstance->SetTurnMessage(TEXT("RandomPlayer Turn"));

	FTimerHandle TimerHandle;
	int32 randTime;
	FCoupleTile Tiles;

	do { randTime = FMath::Rand() % 5; } while (randTime < 2);
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {
		do {
			TArray<ATile*> TilesToRemove;
			int32 ranPiece = FMath::Rand() % ChessBoard->GetBlackPieces().Num();

			SelectedPiece = ChessBoard->GetBlackPieces()[ranPiece];

			if (SelectedPiece != nullptr)
				Piece_SelectableMoves = SelectedPiece->AvaibleMoves(ChessBoard);
			else Piece_SelectableMoves.Empty();

			Tiles.Tile1 = ChessBoard->GetGameField()->GetTileBYXYPosition(SelectedPiece->GetGridPosition().X, SelectedPiece->GetGridPosition().Y);

			for (int32 i = 0; i < Piece_SelectableMoves.Num(); i++)
			{
				Tiles.Tile2 = Piece_SelectableMoves[i];
				if (!ChessBoard->GetAllSelectableMovesByColor(ETileOwner::BLACK).Contains(Tiles))
					TilesToRemove.Add(Piece_SelectableMoves[i]);
			}

			for (int32 i = 0; i < TilesToRemove.Num(); i++)
			{
				Piece_SelectableMoves.Remove(TilesToRemove[i]);
			}

			if (TilesToRemove.Num()>0)
				TilesToRemove.Empty();

		} while (Piece_SelectableMoves.IsEmpty());

		int32 ranTile = FMath::Rand() % Piece_SelectableMoves.Num();

		ATile* SelectedTile = Piece_SelectableMoves[ranTile];

		if (SelectedTile->GetTileStatus() == ETileStatus::OCCUPIED)
			SelectedPiece->Eat(SelectedTile, ChessBoard);

		else SelectedPiece->Move(SelectedTile, ChessBoard->GetGameField());

		SelectedPiece = nullptr;
		Piece_SelectableMoves.Empty();

		AChessGameMode* GameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->TurnNextPlayer();
		IsMyTurn = false;


	}, randTime, false);

	
}

void AChess_RandomPlayer::OnWin()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RandomPlayer won!"));
	GameInstance->SetTurnMessage(TEXT("RandomPlayer Wins"));
}

void AChess_RandomPlayer::OnLose()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RandomPlayer lose!"));
	GameInstance->SetTurnMessage(TEXT("RandomPlayer Loses!"));
}

void AChess_RandomPlayer::OnCheck()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RandomPlayer is in check"));
	GameInstance->SetTurnMessage(TEXT("RandomPlayer in check"));
	OnTurn();
}

void AChess_RandomPlayer::OnStalemate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RandomPlayer in stalemate"));
	GameInstance->SetTurnMessage(TEXT("RandomPlayer in stalemate"));
}

void AChess_RandomPlayer::OnCheckmate()
{
	this->OnLose();
}