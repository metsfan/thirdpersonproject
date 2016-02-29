// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "UnrealNetwork.h"
#include "BaseCharacter.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnergyRegenRate = 25.0;
	EnergyCooloff = 1.0;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (MaxHealth > 0) {
		HealthPercent = (float)Health / (float)MaxHealth;
	}

	if (MaxEnergy > 0) {
		EnergyPercent = (float)Energy / (float)MaxEnergy;
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ABaseCharacter::AddHealth(int32 delta)
{
	if (HasAuthority()) {
		Health += delta;

		if (Health <= 0) {
			// Actor is dead, kill it
			this->Destroy();
		}
	}
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, Health);
	DOREPLIFETIME(ABaseCharacter, MaxHealth);
}

