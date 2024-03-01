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
	SelectableMoves.SetNum(0);
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
	do { randTime = FMath::Rand() % 10; } while (randTime < 2);
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {
		do {
			int32 ranPiece = FMath::Rand() % ChessBoard->GetBlackPieces().Num();

			SelectedPiece = ChessBoard->GetBlackPieces()[ranPiece];

			if (SelectedPiece != nullptr)
				SelectableMoves = SelectedPiece->AvaibleMoves(ChessBoard->GetGameField());
			else SelectableMoves.Empty();

		} while (SelectableMoves.IsEmpty());

		int32 ranTile = FMath::Rand() % SelectableMoves.Num();

		ATile* SelectedTile = SelectableMoves[ranTile];

		if (SelectedTile->GetTileStatus() == ETileStatus::OCCUPIED)
			SelectedPiece->Eat(SelectedTile, ChessBoard);

		else SelectedPiece->Move(SelectedTile, ChessBoard->GetGameField());

		SelectedPiece = nullptr;
		SelectableMoves.Empty();

		AChessGameMode* GameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->TurnNextPlayer();
		IsMyTurn = false;


	}, randTime, false);

	
}

void AChess_RandomPlayer::OnWin()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("RandomPlayer won!"));
	GameInstance->SetTurnMessage(TEXT("RandomPlayer Wins"));
}

void AChess_RandomPlayer::OnLose()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("RandomPlayer lose!"));
	GameInstance->SetTurnMessage(TEXT("RandomPlayer Loses!"));
}