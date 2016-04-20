// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "SpellTriggerSpellEffect.h"
#include "SpellCPP.h"
#include "BaseCharacter.h"

void USpellTriggerSpellEffect::ApplyEffect(TArray<ABaseCharacter*> characters)
{
	auto Owner = Cast<ASpellCPP>(this->GetOwner());
	auto Caster = Cast<ABaseCharacter>(Owner->GetOwner());

	FTransform BaseTransform;
	switch (SpawnLocation) {
	case FSpellTriggerLocation::RelativeToSelfLocation:
		BaseTransform = Owner->GetTransform();
		break;
	case FSpellTriggerLocation::RelativeToOwnerLocation:
		BaseTransform = Caster->GetTransform();
		break;
	case FSpellTriggerLocation::RelativeToWorld:
	default:
		break;
	}

	FTransform FinalTransform = BaseTransform * SpawnTransform;

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = Caster;

	auto SpellData = NewObject<USpellData>(Owner, SpellTrigger);
	auto actor = Cast<ASpellCPP>(GetWorld()->SpawnActor(SpellData->Class, &FinalTransform, spawnParams));
	actor->Instigator = Caster;
	actor->TargetType = SpellData->TargetType;
	if (SpellData->Duration > 0) {
		actor->SetLifeSpan(SpellData->Duration);
	}
}





