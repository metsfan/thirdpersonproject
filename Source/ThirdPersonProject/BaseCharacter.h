// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaseMovementController.h"
#include "SpellData.h"
#include "BaseCharacter.generated.h"

class ASpellCPP;
class UStatusEffect;

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

	UPROPERTY(BlueprintReadWrite)
		bool Sprinting;

	UFUNCTION(Server, Reliable, WithValidation)
		void SetSprinting(bool newSprinting);

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void AddHealth(int32 delta, ABaseCharacter* InstigatorCharacter);
	virtual bool AddHealth_Validate(int32 delta, ABaseCharacter* InstigatorCharacter);
	virtual void AddHealth_Implementation(int32 delta, ABaseCharacter* InstigatorCharacter);

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void AddEnergy(float delta);

	UFUNCTION(BlueprintCallable, Category = Character)
	virtual bool IsAlive();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float RunSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SprintSpeed;

	virtual void OnSpellEffectsApplied(ASpellCPP* Spell);

	void SetMovementSpeedMultiplier(float Value);
	void SetAttackDamageMultiplier(float Value);
	void SetDefenseMultiplier(float Value);
	void SetSizeScale(float Value);

	float GetMovementSpeedMultiplier() { return MovementSpeedMultiplier; }
	float GetAttackDamageMultiplier() { return AttackDamageMultiplier; }
	float GetDefenseMultiplier() { return DefenseMultiplier; }
	float GetSizeScale() { return SizeScale; }

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void AddStatusEffect(TSubclassOf<UStatusEffect> Effect, ABaseCharacter* StatusInstigator);

	void ApplyStatusEffects(float DeltaSeconds);

	const TArray<USpellData*>& GetSpells() { return SpellsArray; }

protected:
	float HealthCooloffTime = 0;
	float EnergyCooloffTime = 0;

	UFUNCTION(Server, Reliable, WithValidation)
	void ResetHealthTimer();

	UFUNCTION(Server, Reliable, WithValidation)
	void ResetEnergyTimer();

	// Status Effect Multipliers
	float MovementSpeedMultiplier;
	float AttackDamageMultiplier;
	float DefenseMultiplier;
	float SizeScale;

	TArray<UStatusEffect*> StatusEffects;

	UPROPERTY()
	TArray<USpellData*> SpellsArray;

private:
	float DeadTime;
};
