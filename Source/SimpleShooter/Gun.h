// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Assets")
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Assets")
	UParticleSystem* BulletHit;

	UPROPERTY(EditAnywhere, Category = "Assets")
	USoundBase* RifleFiredSound;

	UPROPERTY(EditAnywhere, Category = "Assets")
	USoundBase* RifleImpactSound;

	UPROPERTY(EditAnywhere, Category = "Weapon Settings")
	float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Weapon Settings")
	float Damage = 10;
};
