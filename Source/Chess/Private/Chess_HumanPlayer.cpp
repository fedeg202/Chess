// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_HumanPlayer.h"


// Sets default values
AChess_HumanPlayer::AChess_HumanPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SetRootComponent(Camera);

	GameInstance = Cast<UChess_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PlayerNumber = -1;

	Color = EColor::NONE;

	SelectedPiece = nullptr;

}

// Called when the game starts or when spawned
void AChess_HumanPlayer::BeginPlay()
{
	Super::BeginPlay();
	
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

void AChess_HumanPlayer::OnClick()
{
	FHitResult Hit = FHitResult(ForceInit);
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, Hit);
	if (Hit.bBlockingHit && IsMyTurn)
	{
		if (ATile* CurrTile = Cast<ATile>(Hit.GetActor()))
		{
			if (CurrTile->GetTileStatus() == ETileStatus::SELECTABLE && SelectedPiece!=nullptr)
			{
				SelectedPiece->Move(CurrTile,ChessBoard->GetGameField());
				SelectedPiece = nullptr;
				ChessBoard->UnShowSelectableTiles(SelectableMoves);
				SelectableMoves.SetNum(0);
			}
			else if (CurrTile->GetTileStatus() == ETileStatus::OCCUPIED && CurrTile->GetTileOwner() == ETileOwner::WHITE)
			{
				if (SelectedPiece != nullptr)
					ChessBoard->UnShowSelectableTiles(SelectableMoves);

				SelectedPiece = CurrTile->GetOnPiece();

				SelectableMoves = SelectedPiece->AvaibleMoves(ChessBoard->GetGameField());
				ChessBoard->ShowSelectableTiles(SelectableMoves);

			}
			else if (CurrTile->GetTileStatus() == ETileStatus::OCCUPIED && CurrTile->GetTileOwner() == ETileOwner::BLACK && SelectedPiece != nullptr)
			{
				//SelectedPiece->Eat(CurrTile);
			}

		}
		if (APiece* CurrPiece = Cast<APiece>(Hit.GetActor()))
		{
			FVector2D Position = CurrPiece->GetGridPosition();
			ATile* CurrTile = ChessBoard->GetGameField()->GetTileBYXYPosition(Position.X, Position.Y);
			if (CurrTile->GetTileStatus() == ETileStatus::SELECTABLE && SelectedPiece != nullptr)
			{
				SelectedPiece->Move(CurrTile, ChessBoard->GetGameField());
				SelectedPiece = nullptr;
				ChessBoard->UnShowSelectableTiles(SelectableMoves);
				SelectableMoves.SetNum(0);
			}
			else if (CurrTile->GetTileStatus() == ETileStatus::OCCUPIED && CurrTile->GetTileOwner() == ETileOwner::WHITE)
			{
				if (SelectedPiece != nullptr)
					ChessBoard->UnShowSelectableTiles(SelectableMoves);

				SelectedPiece = CurrPiece;

				SelectableMoves = SelectedPiece->AvaibleMoves(ChessBoard->GetGameField());
				ChessBoard->ShowSelectableTiles(SelectableMoves);

			}
			else if (CurrTile->GetTileStatus() == ETileStatus::OCCUPIED && CurrTile->GetTileOwner() == ETileOwner::BLACK && SelectedPiece != nullptr)
			{
				//SelectedPiece->Eat(CurrTile);
			}
			
		}
	}
}


