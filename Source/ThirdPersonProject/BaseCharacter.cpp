// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "UnrealNetwork.h"
#include "MyPlayerState.h"
#include "BaseCharacter.h"
#include "StatusEffect.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnergyRegenRate = 25.0;
	EnergyCooloff = 1.0;

	HealthRegenRate = 100.0;
	HealthCooloff = 1.0;

	bReplicates = true;
	bReplicateMovement = true;

	DespawnTime = 0;
	DeadTime = 0;

	RunSpeed = 600.0f;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentRotation = this->GetActorRotation();
}

void ABaseCharacter::ApplyStatusEffects(float DeltaSeconds)
{
	MovementSpeedMultiplier = 1;
	AttackDamageMultiplier = 1;
	DefenseMultiplier = 1;

	StatusEffects = StatusEffects.FilterByPredicate([](UStatusEffect* Effect) {
		return !Effect->IsExpired();
	});

	for (auto Effect : StatusEffects) {
		Effect->Tick(DeltaSeconds, this);
	}
}

void ABaseCharacter::SetMovementSpeedMultiplier(float Value)
{ 
	MovementSpeedMultiplier += Value; 
}

void ABaseCharacter::SetAttackDamageMultiplier(float Value)
{ 
	AttackDamageMultiplier += Value; 
}

void ABaseCharacter::SetDefenseMultiplier(float Value)
{ 
	DefenseMultiplier += Value; 
}

void ABaseCharacter::SetSizeScale(float Value)
{ 
	SizeScale = Value;
}

// Called every frame
void ABaseCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (this->IsAlive()) {
		if (HasAuthority()) {
			ApplyStatusEffects(DeltaTime);

			EnergyCooloffTime += DeltaTime;

			if (EnergyCooloffTime >= EnergyCooloff && Energy < MaxEnergy) {
				Energy += EnergyRegenRate * DeltaTime;
				Energy = FMath::Min(Energy, MaxEnergy);
			}

			HealthCooloffTime += DeltaTime;

			if (HealthCooloffTime >= HealthCooloff && Health < MaxHealth) {
				Health += HealthRegenRate * DeltaTime;
				Health = FMath::Min(Health, MaxHealth);
			}

			if (Sprinting) {
				if (Energy > 0) {
					this->AddEnergy(-0.25);
					this->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
					this->ResetEnergyTimer();
				}
				else {
					Sprinting = false;
				}
			}
			else {
				this->GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
			}

			this->GetCharacterMovement()->MaxWalkSpeed *= MovementSpeedMultiplier;
		}
	}

	if (MaxHealth > 0) {
		HealthPercent = (float)Health / (float)MaxHealth;
	}

	if (HealthPercent <= 0) {
		DeadTime += DeltaTime;

		if (DeadTime >= DespawnTime) {
			// Actor is dead, kill it
			this->Destroy();
		}
	}

	if (MaxEnergy > 0) {
		EnergyPercent = (float)Energy / (float)MaxEnergy;
	}

	//this->SetActorRotation(CurrentRotation);

	//auto transform = this->GetTransform();
	//transform.SetRotation(CurrentRotation.Quaternion());
	//this->SetActorTransform(transform);
}

bool ABaseCharacter::SetSprinting_Validate(bool newSprinting)
{
	return true;
}

void ABaseCharacter::SetSprinting_Implementation(bool newSprinting)
{
	Sprinting = newSprinting;
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

bool ABaseCharacter::AddHealth_Validate(int32 delta, ABaseCharacter* InstigatorCharacter)
{
	return true;
}

void ABaseCharacter::AddHealth_Implementation(int32 delta, ABaseCharacter* InstigatorCharacter)
{
	float HealthDelta = delta;
	if (HealthDelta < 0) {
		// This is damage, so we need to apply attack and defense multipliers
		HealthDelta *= InstigatorCharacter->GetAttackDamageMultiplier() * DefenseMultiplier;
	}
	Health = FMath::Clamp<int32>(Health + HealthDelta, 0, MaxHealth);

	if (HealthDelta < 0) {
		this->ResetHealthTimer();
	}

	UE_LOG(MyLog, Log, TEXT("A character took some damage: %d"), delta);
}

bool ABaseCharacter::IsAlive()
{
	return Health > 0;
}

bool ABaseCharacter::AddEnergy_Validate(float delta)
{
	return true;
}

void ABaseCharacter::AddEnergy_Implementation(float delta)
{
	Energy += delta;
}

bool ABaseCharacter::ResetHealthTimer_Validate()
{
	return true;
}

void ABaseCharacter::ResetHealthTimer_Implementation()
{
	HealthCooloffTime = 0;
}

bool ABaseCharacter::ResetEnergyTimer_Validate()
{
	return true;
}

void ABaseCharacter::ResetEnergyTimer_Implementation()
{
	EnergyCooloffTime = 0;
}

void ABaseCharacter::OnSpellEffectsApplied(ASpellCPP* Spell)
{
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, Health);
	DOREPLIFETIME(ABaseCharacter, MaxHealth);
	DOREPLIFETIME(ABaseCharacter, Energy);
	DOREPLIFETIME(ABaseCharacter, MaxEnergy);
	DOREPLIFETIME(ABaseCharacter, CurrentRotation);
}

bool ABaseCharacter::AddStatusEffect_Validate(TSubclassOf<UStatusEffect> Effect, ABaseCharacter* StatusInstigator)
{
	return true;
}

void ABaseCharacter::AddStatusEffect_Implementation(TSubclassOf<UStatusEffect> Effect, ABaseCharacter* StatusInstigator)
{
	UStatusEffect* ExistingEffect = nullptr;
	for (auto StatusEffect : StatusEffects) {
		if (Effect == StatusEffect->GetClass()) {
			ExistingEffect = StatusEffect;
			break;
		}
	}

	if (ExistingEffect) {
		ExistingEffect->AddStack();
	}
	else {
		auto NewStatus = NewObject<UStatusEffect>(this, Effect);
		NewStatus->Instigator = StatusInstigator;
		StatusEffects.Add(NewStatus);
	}
}

