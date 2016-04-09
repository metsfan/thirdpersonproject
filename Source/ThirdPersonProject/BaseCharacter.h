// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaseMovementController.h"
#include "BaseCharacter.generated.h"

class ASpellCPP;

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

	virtual bool IsPlayerControlled() { return false; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, Replicated)
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, Replicated)
		float MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = Default)
		float HealthPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float HealthRegenRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float HealthCooloff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, Replicated)
		float Energy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, Replicated)
		float MaxEnergy;

	UPROPERTY(BlueprintReadOnly, Category = Default)
		float EnergyPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float EnergyRegenRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float EnergyCooloff;

	UPROPERTY(BlueprintReadWrite, Category = Controllers)
		ABaseMovementController* MovementController;

	UPROPERTY(Replicated)
		FRotator CurrentRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Character)
		float DespawnTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Character)
		int32 TeamID;

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void AddHealth(int32 delta);
	virtual bool AddHealth_Validate(int32 delta);
	virtual void AddHealth_Implementation(int32 delta);

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void AddEnergy(float delta);

	UFUNCTION(BlueprintCallable, Category = Character)
	virtual bool IsAlive();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float RunSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SprintSpeed;

	virtual void OnSpellEffectsApplied(ASpellCPP* Spell);

protected:
	float HealthCooloffTime = 0;
	float EnergyCooloffTime = 0;

	UFUNCTION(Server, Reliable, WithValidation)
	void ResetHealthTimer();

	UFUNCTION(Server, Reliable, WithValidation)
	void ResetEnergyTimer();

private:
	float DeadTime;
};
