// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "EnemyAICharacter.generated.h"

UCLASS()
class SUPERTIMECOMMANDO_API AEnemyAICharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Visualizer, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ULoSVisualizer* Visualizer;

public:
	UPROPERTY(Category = Patrol, EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> PatrolPoints;

public:
	// Sets default values for this character's properties
	AEnemyAICharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
