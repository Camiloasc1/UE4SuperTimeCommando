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
				Die();
				SetLifeSpan(0);
				SetActorTickEnabled(false);
			}
		}
	}
	else
	{
		// Go forward
		FVector ToTarget = Target - GetActorLocation();
		if (ToTarget.Size() > 1)
		{
			AddActorWorldOffset(ToTarget.GetSafeNormal() * Speed * DeltaTime);
		}
		else if (DeathTime == 0)
		{
			Die();
		}
	}
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ASuperTimeCommandoCharacter::StaticClass()))
	{
		Cast<ASuperTimeCommandoCharacter>(OtherActor)->AddHit();
		Die();
	}
}

void AProjectile::Respawn()
{
	DeathTime = 0;
	SetActorHiddenInGame(false);
}

void AProjectile::Die()
{
	SetActorHiddenInGame(true);
	DeathTime = GetWorld()->GetTimeSeconds();
}
