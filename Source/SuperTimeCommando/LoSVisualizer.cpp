// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "LoSVisualizer.h"


// Sets default values
ALoSVisualizer::ALoSVisualizer()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALoSVisualizer::BeginPlay()
{
	Super::BeginPlay();

	UpdateSphereRadius();
}

// Called every frame
void ALoSVisualizer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
#if WITH_EDITOR
void ALoSVisualizer::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//Get the name of the property that was changed
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	// We test using GET_MEMBER_NAME_CHECKED so that if someone changes the property name
	// in the future this will fail to compile and we can update it.
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ALoSVisualizer, MaxDistance))
	{
		UpdateSphereRadius();
	}
}
#endif

void ALoSVisualizer::UpdateSphereRadius()
{
	Sphere->SetSphereRadius(MaxDistance);
}
