// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_HumanPlayer.h"
#include "ChessGameMode.h"
#include "Chess_PlayerController.h"
#include "Blueprint/UserWidget.h"


// Sets default values
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

}

// Called when the game starts or when spawned
void AChess_HumanPlayer::BeginPlay()
{
	Super::BeginPlay();

	AChess_PlayerController* PC = GetController<AChess_PlayerController>();
	check(PC);
	ChessHUD = CreateWidget<UChessHUD>(PC, PC->ChessHUDClass);
	check(ChessHUD); 
	ChessHUD->AddToPlayerScreen();

	PawnPromotionHUD = CreateWidget<UPawnPromotionHUD>(PC, PC->PawnPromotionHUDClass);
	check(PawnPromotionHUD);
	
}

// Called every frame
void AChess_HumanPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChess_HumanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AChess_HumanPlayer::OnTurn()
{
	IsMyTurn = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Your Turn"));
	GameInstance->SetTurnMessage(TEXT("Human Turn"));
}

void AChess_HumanPlayer::OnWin()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You won!"));
	GameInstance->SetTurnMessage(TEXT("Human Wins"));
}

void AChess_HumanPlayer::OnLose()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You lose!"));
	GameInstance->SetTurnMessage(TEXT("Human Loses!"));
}

void AChess_HumanPlayer::OnCheck()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You're in check"));
	GameInstance->SetTurnMessage(TEXT("Human in check"));
	IsMyTurn = true;
}

void AChess_HumanPlayer::OnStalemate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You're in stalemate"));
	GameInstance->SetTurnMessage(TEXT("Human in stalemate"));
}

void AChess_HumanPlayer::OnCheckmate()
{
	this->OnLose();
}

void AChess_HumanPlayer::OnClick()
{
	FHitResult Hit = FHitResult(ForceInit);
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, Hit);
	ATile* CurrTile = nullptr;
	FCoupleTile Tiles;
	TArray<ATile*> TilesToRemove;

	if (Hit.bBlockingHit && IsMyTurn)
	{
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
				 
				ChessBoard->UnShowSelectableTiles(Piece_SelectableMoves);
				Piece_SelectableMoves.Empty();

				if (!ChessBoard->CheckPawnPromotion(SelectedPiece))
				{
					ChessHUD->AddMoveButtonToTheHistoryScrollBox(ChessBoard->CreateMoveString(SelectedPiece,Tiles), Color);
					SelectedPiece = nullptr;
					AChessGameMode* GameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());
					IsMyTurn = false;
					GameMode->TurnNextPlayer();
				}
				else 
				{
					IsMyTurn = false;
					PawnPromotionHUD->AddToPlayerScreen();
				}
			}
			else if (CurrTile->GetTileStatus() == ETileStatus::OCCUPIED && CurrTile->GetTileOwner() == ETileOwner::WHITE)
			{
				if (SelectedPiece != nullptr)
					ChessBoard->UnShowSelectableTiles(Piece_SelectableMoves);

				SelectedPiece = CurrTile->GetOnPiece();

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
				ChessBoard->UnShowSelectableTiles(Piece_SelectableMoves);

				if (!ChessBoard->CheckPawnPromotion(SelectedPiece))
				{
					ChessHUD->AddMoveButtonToTheHistoryScrollBox(ChessBoard->CreateMoveString(SelectedPiece, Tiles), Color);
					SelectedPiece = nullptr;
					AChessGameMode* GameMode = Cast<AChessGameMode>(GetWorld()->GetAuthGameMode());
					IsMyTurn = false;
					GameMode->TurnNextPlayer();
				}
				else
				{
					ChessHUD->AddMoveButtonToTheHistoryScrollBox(ChessBoard->CreateMoveString(SelectedPiece, Tiles, true, true), Color);
					IsMyTurn = false;
					PawnPromotionHUD->AddToPlayerScreen();
				}

				Piece_SelectableMoves.Empty();
				SelectedPiece = nullptr;

			}
		}
		
				
	}
}


