// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

private:
	UPROPERTY(EditAnywhere, Category = "Default")
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY()
	UUserWidget* HUDScreen;

	UPROPERTY(EditAnywhere, Category = "Default")
	TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere, Category = "Default")
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere, Category = "Default")
	float RestartDelay = 1.f;

	FTimerHandle RestartTimer;
};
