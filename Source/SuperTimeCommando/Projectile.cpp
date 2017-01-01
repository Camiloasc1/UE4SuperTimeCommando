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

	ActorHistory = CreateDefaultSubobject<UActorHistory>(TEXT("ActorHistory"));
	ActorHistory->SetupAttachment(RootComponent);

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

	FVector Movement = Target - GetActorLocation();
	if (Movement.Size() < 5)
	{
		SetActorHiddenInGame(true);
	}
	AddActorWorldOffset(Movement.GetSafeNormal() * Speed * DeltaTime);
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ASuperTimeCommandoCharacter::StaticClass()))
	{
		Cast<ASuperTimeCommandoCharacter>(OtherActor)->AddHit();
		SetActorHiddenInGame(true);
	}
}
