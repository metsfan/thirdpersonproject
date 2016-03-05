// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "BaseCharacter.h"
#include "UnrealNetwork.h"
#include "MyPlayerState.h"

AMyPlayerState::AMyPlayerState(): Super()
{
	this->bReplicates = true;
}

void AMyPlayerState::Update(ABaseCharacter* Character)
{
	Health = Character->Health;
	MaxHealth = Character->MaxHealth;
	HealthPercent = Character->HealthPercent;

	Energy = Character->Energy;
	MaxEnergy = Character->MaxEnergy;
	EnergyPercent = Character->EnergyPercent;

	if (Name != Character->Name) {
		Name = Character->Name;
	}
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerState, Health);
	DOREPLIFETIME(AMyPlayerState, MaxHealth);
	DOREPLIFETIME(AMyPlayerState, HealthPercent);
	DOREPLIFETIME(AMyPlayerState, Energy);
	DOREPLIFETIME(AMyPlayerState, MaxEnergy);
	DOREPLIFETIME(AMyPlayerState, EnergyPercent);
	DOREPLIFETIME(AMyPlayerState, Name);
}


