// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaseMovementController.h"
#include "BaseCharacter.generated.h"

UCLASS()
class THIRDPERSONPROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void ABaseCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, Replicated)
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, Replicated)
		float MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = Default)
		float HealthPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float Energy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MaxEnergy;

	UPROPERTY(BlueprintReadOnly, Category = Default)
		float EnergyPercent;

	UPROPERTY(BlueprintReadWrite, Category = Stats)
		float EnergyRegenRate;

	UPROPERTY(BlueprintReadWrite, Category = Stats)
		float EnergyCooloff;

	UPROPERTY(BlueprintReadWrite, Category = Controllers)
		ABaseMovementController* MovementController;

	UFUNCTION()
	void AddHealth(int32 delta);
};
