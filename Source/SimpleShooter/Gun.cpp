// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"

#define OUT

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(RifleFiredSound, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (!OwnerController) return;
	FVector PVLocation;
	FRotator PVRotation;
	OwnerController->GetPlayerViewPoint(OUT PVLocation, OUT PVRotation);

	FVector End = PVLocation + PVRotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());


	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(OUT Hit, PVLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params))
	{
		FVector Spawn = Hit.Location - PVLocation;
		Spawn = PVLocation + (0.9 * Spawn);
		FVector ShotDirection = -PVRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletHit, Spawn, ShotDirection.Rotation());
		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), RifleImpactSound, GetActorLocation());
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			//UE_LOG(LogTemp, Warning, TEXT("Actor Hit: %s"), *HitActor->GetName());
		}
	}

}

