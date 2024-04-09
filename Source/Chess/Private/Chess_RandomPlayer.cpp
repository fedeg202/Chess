// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_RandomPlayer.h"
#include "ChessGameMode.h"
#include "Chess_PlayerController.h"
#include "Components/AudioComponent.h"

/**
 * @brief AChess_RandomPlayer class constructor
 *
 */
AChess_RandomPlayer::AChess_RandomPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* NewRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	RootComponent = NewRootComponent;

	GameInstance = Cast<UChess_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	Color = EColor::NONE;

	SelectedPiece = nullptr;
	Piece_SelectableMoves.SetNum(0);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));

}

/**
 * @brief Called when starting playing or on spawn
 *
 */
void AChess_RandomPlayer::BeginPlay()
{
	Super::BeginPlay();

}

/**
 * @brief Called every tick
 *
 */
void AChess_RandomPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**
 * @brief Called to setup the input component
 *
 */
void AChess_RandomPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/**
 * @brief Called when the player start his turn
 *
 */
void AChess_RandomPlayer::OnTurn()
{
	if (ChessHUD == nullptr)
	{
		AChess_PlayerController* PC = Cast<AChess_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
		ChessHUD = PC->ChessHUD;
	}
		
	IsMyTurn = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RandomPlayer Turn"));
	
	if(!b_OnCheck) GameInstance->SetTurnMessage("RandomPlayer in Turn");

	if (SelectedPiece != nullptr)
		SelectedPiece->UnshowSelected();

	FTimerHandle TimerHandle;
	int32 randTime;



	do { randTime = FMath::Rand() % 5; } while (randTime < 2);
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {
		FCoupleTile Tiles;
		bool b_eatFlag = false;

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

		SelectedPiece->ShowSelected();

		int32 ranTile = FMath::Rand() % Piece_SelectableMoves.Num();

		ATile* SelectedTile = Piece_SelectableMoves[ranTile];
		
		Tiles.Tile1 = ChessBoard->GetGameField()->GetTileBYXYPosition(SelectedPiece->GetGridPosition().X, SelectedPiece->GetGridPosition().Y);
		Tiles.Tile2 = SelectedTile;

		if (SelectedTile->GetTileStatus() == ETileStatus::OCCUPIED)
		{
			SelectedPiece->Eat(SelectedTile, ChessBoard);

			PlaySound(4);

			b_eatFlag = true;
		}
		
		else
		{
			SelectedPiece->Move(SelectedTile, ChessBoard->GetGameField());
			PlaySound(0);
		}

		AChessGameMode* GameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());

		IsMyTurn = false;
		Piece_SelectableMoves.Empty();

		if (!ChessBoard->CheckPawnPromotion(SelectedPiece))
		{
			ChessHUD->AddMoveButtonToTheHistoryScrollBox(ChessBoard->CreateMoveString(SelectedPiece, Tiles, b_eatFlag, false), Color);
			ChessBoard->AddMove(FMove(Tiles, Color, b_eatFlag,false));
			GameMode->TurnNextPlayer();
		}
		else
		{
			ChessHUD->AddMoveButtonToTheHistoryScrollBox(ChessBoard->CreateMoveString(SelectedPiece, Tiles, b_eatFlag, true), Color);
			ChessBoard->AddMove(FMove(Tiles, Color, b_eatFlag, false));
			int32 randPromotion = FMath::Rand() % 4;
			switch (randPromotion)
			{
			case 0:
				GameMode->HandlePawnPromotion(EPieceColor::BLACK, EPieceName::ROOK);
				break;
			case 1:
				GameMode->HandlePawnPromotion(EPieceColor::BLACK, EPieceName::KNIGHT);
				break;
			case 2:
				GameMode->HandlePawnPromotion(EPieceColor::BLACK, EPieceName::BISHOP);
				break;
			case 3:
				GameMode->HandlePawnPromotion(EPieceColor::BLACK, EPieceName::QUEEN);
				break;
			}
		}
	}, randTime, false);

	
}

/**
 * @brief Called when the player win
 *
 */
void AChess_RandomPlayer::OnWin()
{
	if (SelectedPiece != nullptr)
		SelectedPiece->UnshowSelected();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RandomPlayer won!"));
	//GameInstance->SetTurnMessage(TEXT("RandomPlayer Wins"));
}

/**
 * @brief Called when the player lose
 *
 */
void AChess_RandomPlayer::OnLose()
{
	if (SelectedPiece != nullptr)
		SelectedPiece->UnshowSelected();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RandomPlayer lose!"));
	//GameInstance->SetTurnMessage(TEXT("RandomPlayer Loses!"));
}

/**
 * @brief Called when the player is in check
 *
 */
void AChess_RandomPlayer::OnCheck()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RandomPlayer is in check"));
	GameInstance->SetTurnMessage(TEXT("RandomPlayer in check"));
	OnTurn();
}

/**
 * @brief Called when the player is in stalemate or draw
 *
 */
void AChess_RandomPlayer::OnStalemate()
{
	if (SelectedPiece != nullptr)
		SelectedPiece->UnshowSelected();

	
	if (b_OnStalemate)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RandomPlayer in stalemate"));
		GameInstance->SetTurnMessage(TEXT("RandomPlayer in stalemate"));
		PlaySound(3);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Draw by repetition!"));
		GameInstance->SetTurnMessage(TEXT("Draw by repetition!"));
	}
	
}

/**
 * @brief Called when the player is in checkmate
 *
 */
void AChess_RandomPlayer::OnCheckmate()
{
	this->OnLose();
}
/**
 * @brief Method to play a sound during game
 *
 * @param SoundIndex index of the sound to play (4 is the one of the eat or capture and there are 3 different sounds of the capture chosen randomly)
 */
void AChess_RandomPlayer::PlaySound(int32 SoundIndex)
{
	if (SoundIndex == 4)
		SoundIndex = FMath::RandRange(4, 6);

	if (SoundsToPlay[SoundIndex])
		AudioComponent->SetSound(SoundsToPlay[SoundIndex]);
	AudioComponent->Play();
}
