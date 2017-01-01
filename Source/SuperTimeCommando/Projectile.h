// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class SUPERTIMECOMMANDO_API AProjectile : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Sphere;
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UActorHistory* ActorHistory;

public:
	UPROPERTY()
	FVector Origin;
	UPROPERTY()
	FVector Target;
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float Speed;

public:
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
