// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "Target.h"
#include "SuperTimeCommandoGameState.h"
#include "SuperTimeCommandoCharacter.h"


// Sets default values
ATarget::ATarget()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Sphere"));
	Box->OnComponentBeginOverlap.AddDynamic(this, &ATarget::OnBeginOverlap);
	RootComponent = Box;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATarget::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATarget::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ASuperTimeCommandoCharacter::StaticClass()))
	{
		ASuperTimeCommandoGameState* GameState = GetWorld()->GetGameState<ASuperTimeCommandoGameState>();
		GameState->Win();
	}
}
