// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "UnrealNetwork.h"
#include "MyPlayerState.h"
#include "BaseCharacter.h"

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
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentRotation = this->GetActorRotation();
}

// Called every frame
void ABaseCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (this->IsAlive()) {
		if (HasAuthority()) {
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
	Health = FMath::Clamp<int32>(Health + delta, 0, MaxHealth);

	if (delta < 0) {
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

