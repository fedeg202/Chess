// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_HumanPlayer.h"
#include "ChessGameMode.h"
#include "Chess_PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"



/**
* @brief AChess_HumanPlayer class contructor
*/
AChess_HumanPlayer::AChess_HumanPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SetRootComponent(Camera);

	GameInstance = Cast<UChess_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));


	Color = EColor::NONE;

	SelectedPiece = nullptr;
	Piece_SelectableMoves.SetNum(0);

	b_OnCheck = b_OnCheckmate = b_OnStalemate = false;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
}

/**
 * @brief Called when the game starts or when spawned
 *
 */
void AChess_HumanPlayer::BeginPlay()
{
	Super::BeginPlay();

	AChess_PlayerController* PC = GetController<AChess_PlayerController>();
	check(PC);
	PC->ChessHUD = CreateWidget<UChessHUD>(PC, PC->ChessHUDClass);
	check(PC->ChessHUD);
	ChessHUD = PC->ChessHUD;
	PC->PawnPromotionHUD = CreateWidget<UPawnPromotionHUD>(PC, PC->PawnPromotionHUDClass);
	check(PC->PawnPromotionHUD);
	PawnPromotionHUD = PC->PawnPromotionHUD;
}

/**
 * @brief Called every frame
 *
 */
void AChess_HumanPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**
 * @brief Called to bind functionality to input
 *
 */
void AChess_HumanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/**
 * @brief Called when the player is on turn
 *
 */
void AChess_HumanPlayer::OnTurn()
{
	IsMyTurn = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Your Turn"));
	GameInstance->SetTurnMessage(TEXT("Human Turn"));
}

/**
 * @brief Called when the player win
 *
 */
void AChess_HumanPlayer::OnWin()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You won!"));
	GameInstance->SetTurnMessage(TEXT("Human Wins"));
	PlaySound(1);
}

/**
 * @brief Called when the player lose
 *
 */
void AChess_HumanPlayer::OnLose()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You lose!"));
	GameInstance->SetTurnMessage(TEXT("Human Loses!"));
	PlaySound(2);
}

/**
 * @brief Called when the player is in check
 *
 */
void AChess_HumanPlayer::OnCheck()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You're in check"));
	GameInstance->SetTurnMessage(TEXT("Human in check"));
	IsMyTurn = true;
}

/**
 * @brief Called when the player is in stalemate or draw
 *
 */
void AChess_HumanPlayer::OnStalemate()
{
	if (b_OnStalemate)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You're in stalemate"));
		GameInstance->SetTurnMessage(TEXT("Human in stalemate"));
		PlaySound(3);
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Draw by repetition!"));
		GameInstance->SetTurnMessage(TEXT("Draw by repetition!"));
	}
}

/**
 * @brief Called when the player is on checkmate
 *
 */
void AChess_HumanPlayer::OnCheckmate()
{
	this->OnLose();
}

/**
 * @brief Called to handle the clicks
 *
 */
void AChess_HumanPlayer::OnClick()
{
	FHitResult Hit = FHitResult(ForceInit);
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, Hit);
	ATile* CurrTile = nullptr;
	FCoupleTile Tiles;
	TArray<ATile*> TilesToRemove;

	if (Hit.bBlockingHit && IsMyTurn)
	{
		//Gettin the hitten tile
		if (ATile* HitTile = Cast<ATile>(Hit.GetActor()))
		{
			CurrTile = HitTile;
		}
		else if (APiece* CurrPiece = Cast<APiece>(Hit.GetActor()))
		{
			FVector2D Position = CurrPiece->GetGridPosition();
			CurrTile = ChessBoard->GetGameField()->GetTileBYXYPosition(Position.X, Position.Y);
		}

		if (CurrTile != nullptr) 
		{
			if (CurrTile->GetTileStatus() == ETileStatus::SELECTABLE && SelectedPiece != nullptr)
			{
				Tiles.Tile1 = ChessBoard->GetGameField()->GetTileBYXYPosition(SelectedPiece->GetGridPosition().X, SelectedPiece->GetGridPosition().Y);
				Tiles.Tile2 = CurrTile;

				SelectedPiece->Move(CurrTile, ChessBoard->GetGameField());

				PlaySound(0);
				 
				ChessBoard->UnShowSelectableTiles(Piece_SelectableMoves);
				SelectedPiece->UnshowSelected();
				Piece_SelectableMoves.Empty();

				if (!ChessBoard->CheckPawnPromotion(SelectedPiece))
				{
					ChessHUD->AddMoveButtonToTheHistoryScrollBox(ChessBoard->CreateMoveString(SelectedPiece,Tiles), Color);
					ChessBoard->AddMove(FMove(Tiles, Color));
					SelectedPiece = nullptr;
					AChessGameMode* GameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());
					IsMyTurn = false;
					GameMode->TurnNextPlayer();
				}
				else 
				{
					ChessHUD->AddMoveButtonToTheHistoryScrollBox(ChessBoard->CreateMoveString(SelectedPiece, Tiles, false, true), Color);
					ChessBoard->AddMove(FMove(Tiles, Color,false,true));
					IsMyTurn = false;
					PawnPromotionHUD->AddToPlayerScreen();
				}
			}
			else if (CurrTile->GetTileStatus() == ETileStatus::OCCUPIED && CurrTile->GetTileOwner() == ETileOwner::WHITE)
			{
				if (SelectedPiece != nullptr)
				{
					ChessBoard->UnShowSelectableTiles(Piece_SelectableMoves);
					SelectedPiece->UnshowSelected();
				}
					

				SelectedPiece = CurrTile->GetOnPiece();
				SelectedPiece->ShowSelected();

				Piece_SelectableMoves = SelectedPiece->AvaibleMoves(ChessBoard);
				Tiles.Tile1 = CurrTile;

				for (int32 i = 0; i < Piece_SelectableMoves.Num(); i++) 
				{
					Tiles.Tile2 = Piece_SelectableMoves[i];
					if (!ChessBoard->GetAllSelectableMovesByColor(ETileOwner::WHITE).Contains(Tiles))
						TilesToRemove.Add(Piece_SelectableMoves[i]);
				}

				for (int32 i = 0; i < TilesToRemove.Num(); i++) 
				{
					Piece_SelectableMoves.Remove(TilesToRemove[i]);
				}

				ChessBoard->ShowSelectableTiles(Piece_SelectableMoves);


			}
			else if (CurrTile->GetTileStatus() == ETileStatus::EATABLE && SelectedPiece != nullptr)
			{
				Tiles.Tile1 = ChessBoard->GetGameField()->GetTileBYXYPosition(SelectedPiece->GetGridPosition().X, SelectedPiece->GetGridPosition().Y);
				Tiles.Tile2 = CurrTile;

				SelectedPiece->Eat(CurrTile,ChessBoard);
				SelectedPiece->UnshowSelected();

				PlaySound(4);

				ChessBoard->UnShowSelectableTiles(Piece_SelectableMoves);

				if (!ChessBoard->CheckPawnPromotion(SelectedPiece))
				{
					ChessHUD->AddMoveButtonToTheHistoryScrollBox(ChessBoard->CreateMoveString(SelectedPiece, Tiles,true), Color);
					ChessBoard->AddMove(FMove(Tiles, Color,true));
					SelectedPiece = nullptr;
					AChessGameMode* GameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());
					IsMyTurn = false;
					GameMode->TurnNextPlayer();
				}
				else
				{
					ChessHUD->AddMoveButtonToTheHistoryScrollBox(ChessBoard->CreateMoveString(SelectedPiece, Tiles, true, true), Color);
					ChessBoard->AddMove(FMove(Tiles, Color, true,true));
					IsMyTurn = false;
					PawnPromotionHUD->AddToPlayerScreen();
				}

				Piece_SelectableMoves.Empty();
				SelectedPiece = nullptr;

			}
		}
		
				
	}
}

/**
 * @brief Method to play a sound during game
 * 
 * @param SoundIndex index of the sound to play (4 is the one of the eat or capture and there are 3 different sounds of the capture chosen randomly)
 */
void AChess_HumanPlayer::PlaySound(int32 SoundIndex)
{
	if (SoundIndex == 4)
		SoundIndex = FMath::RandRange(4, 6);

	if (SoundsToPlay[SoundIndex])
		AudioComponent->SetSound(SoundsToPlay[SoundIndex]);
	AudioComponent->Play();
}
/**
 * @brief Method to change the human player camera position, toggle between 4 positions
 *
 */
void AChess_HumanPlayer::ChangeCameraPosition()
{
	CameraPosition++;
	float CameraPosX = 0;
	float CameraPosY = 0;
	FVector CameraPos;

	switch (CameraPosition)
	{
	case 0:
		CameraPosX = (ChessBoard->GetGameField()->TileSize * (ChessBoard->GetGameField()->Size - 1)) / 2;
		CameraPos = FVector(CameraPosX, CameraPosX, 1050.0f);
		SetActorLocationAndRotation(CameraPos, FRotationMatrix::MakeFromX(FVector(0, 0, -1)).Rotator());
		break;
	case 1: 
		CameraPosX = (ChessBoard->GetGameField()->TileSize * -4);
		CameraPosY = (ChessBoard->GetGameField()->TileSize * (ChessBoard->GetGameField()->Size-1)) / 2;
		CameraPos = FVector(CameraPosX, CameraPosY, 850.0f);
		SetActorLocationAndRotation(CameraPos, FRotationMatrix::MakeFromX(FVector(1, 0, -1)).Rotator());
		break;
	case 2:
		CameraPosX = (ChessBoard->GetGameField()->TileSize * (ChessBoard->GetGameField()->Size - 1)) / 2;
		CameraPosY = (ChessBoard->GetGameField()->TileSize * (ChessBoard->GetGameField()->Size + 3));
		CameraPos = FVector(CameraPosX, CameraPosY, 850.0f);
		SetActorLocationAndRotation(CameraPos, FRotationMatrix::MakeFromX(FVector(0, -1, -1)).Rotator());
		break;
	case 3:
		CameraPosX = (ChessBoard->GetGameField()->TileSize * (ChessBoard->GetGameField()->Size - 1)) / 2;
		CameraPosY = (ChessBoard->GetGameField()->TileSize * -4);
		CameraPos = FVector(CameraPosX, CameraPosY, 850.0f);
		SetActorLocationAndRotation(CameraPos, FRotationMatrix::MakeFromX(FVector(0, 1, -1)).Rotator());
		break;
	default:
		CameraPosition = -1;
		ChangeCameraPosition();
		break;
	}
}


