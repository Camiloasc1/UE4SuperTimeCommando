// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "LoS/LoSVisualizer.h"
#include "EnemyAICharacter.h"


// Sets default values
AEnemyAICharacter::AEnemyAICharacter()
{
	Visualizer = CreateDefaultSubobject<ULoSVisualizer>(TEXT("Visualizer"));
	Visualizer->SetupAttachment(RootComponent);

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

#if WITH_EDITOR
void AEnemyAICharacter::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedChainEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedChainEvent);

	int32 i = PropertyChangedChainEvent.GetArrayIndex(TEXT("PatrolPoints"));
	if (i == 0)
	{
		SetActorLocation(PatrolPoints[0]->GetActorLocation());
	}
}
#endif

// Called when the game starts or when spawned
void AEnemyAICharacter::BeginPlay()
{
	Super::BeginPlay();

	// Move to first patrol point
	if (PatrolPoints.Num() > 0)
	{
		SetActorLocation(PatrolPoints[0]->GetActorLocation());
	}
}

// Called every frame
void AEnemyAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
