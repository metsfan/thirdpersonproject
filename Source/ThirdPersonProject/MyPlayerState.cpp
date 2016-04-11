// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "BaseCharacter.h"
#include "UnrealNetwork.h"
#include "MyPlayerState.h"

AMyPlayerState::AMyPlayerState(): Super(), ReadyToRestart(false)
{
	this->bReplicates = true;
}

void AMyPlayerState::Update(ABaseCharacter* Character)
{
	if (Character) {
		Health = Character->Health;
		MaxHealth = Character->MaxHealth;
		HealthPercent = Character->HealthPercent;

		Energy = Character->Energy;
		MaxEnergy = Character->MaxEnergy;
		EnergyPercent = Character->EnergyPercent;

		/*if (Name != Character->Name) {
			Name = Character->Name;
		}*/
		Name = FText::AsNumber(PlayerId).ToString();
	}
	else {
		Health = 0;
		MaxHealth = 0;
		HealthPercent = 0;
	}
}

bool AMyPlayerState::SetPlayerReady_Validate(bool ready)
{
	return true;
}

void AMyPlayerState::SetPlayerReady_Implementation(bool ready)
{
	ReadyToRestart = true;
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
	DOREPLIFETIME(AMyPlayerState, ReadyToRestart);
	DOREPLIFETIME(AMyPlayerState, Kills);
	DOREPLIFETIME(AMyPlayerState, Assists);
	DOREPLIFETIME(AMyPlayerState, DamageDone);
	DOREPLIFETIME(AMyPlayerState, DamageTaken);
	DOREPLIFETIME(AMyPlayerState, ReadyToPlay);
}


