// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "Projectile.h"
#include "ActorHistory.h"
#include "SuperTimeCommandoCharacter.h"


// Sets default values
AProjectile::AProjectile()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
	RootComponent = Sphere;


	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	Origin = GetActorLocation();

	ASuperTimeCommandoGameState* GameState = GetWorld()->GetGameState<ASuperTimeCommandoGameState>();
	GameState->OnTimeBeginBackward.AddDynamic(this, &AProjectile::OnTimeBeginBackward);
	GameState->OnTimeEndBackward.AddDynamic(this, &AProjectile::OnTimeEndBackward);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	bool IsTimeBackward = GetWorld()->GetGameState<ASuperTimeCommandoGameState>()->IsTimeBackward();

	if (IsTimeBackward)
	{
		// Wait until death time
		ASuperTimeCommandoGameState* GameState = GetWorld()->GetGameState<ASuperTimeCommandoGameState>();
		float CurrentTime = GetWorld()->GetTimeSeconds();
		float PivotTime = GameState->GetTimePivot();
		if (CurrentTime - PivotTime >= PivotTime - DeathTime || DeathTime == 0)
		{
			// Respawn if is necessary
			if (DeathTime != 0)
			{
				Respawn();
			}
			// Go back
			FVector ToOrigin = Origin - GetActorLocation();
			if (ToOrigin.Size() > 1)
			{
				AddActorWorldOffset(ToOrigin.GetSafeNormal() * Speed * DeltaTime);
			}
			else
			{
				// Destroy
				Die(false);
				SetLifeSpan(DELTA);
				SetActorTickEnabled(false);
			}
		}
	}
	else if (DeathTime == 0)
	{
		// Go forward
		FVector ToTarget = Target - GetActorLocation();
		if (ToTarget.Size() > 1)
		{
			AddActorWorldOffset(ToTarget.GetSafeNormal() * Speed * DeltaTime);
		}
		else
		{
			Die(false);
		}
	}
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetWorld()->GetGameState<ASuperTimeCommandoGameState>()->IsTimeBackward())
	{
		return;
	}

	if (OtherActor->IsA(ASuperTimeCommandoCharacter::StaticClass()))
	{
		Die(true);
	}
}

void AProjectile::OnTimeBeginBackward()
{
}

void AProjectile::OnTimeEndBackward()
{
	if (DeathTime != 0)
	{
		float Delta = GetWorld()->GetTimeSeconds() - GetWorld()->GetGameState<ASuperTimeCommandoGameState>()->GetTimePivot();
		DeathTime += 2 * Delta;
	}
}

void AProjectile::Respawn()
{
	if (WasHit)
	{
		ASuperTimeCommandoGameState* GameState = GetWorld()->GetGameState<ASuperTimeCommandoGameState>();
		GameState->UndoHit();
	}
	WasHit = false;
	DeathTime = 0;
	SetActorHiddenInGame(false);
}

void AProjectile::Die(bool IsHit)
{
	if (IsHit)
	{
		ASuperTimeCommandoGameState* GameState = GetWorld()->GetGameState<ASuperTimeCommandoGameState>();
		GameState->AddHit();
	}
	WasHit = IsHit;
	DeathTime = GetWorld()->GetTimeSeconds();
	SetActorHiddenInGame(true);
}
