// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "SpellTriggerSpellEffect.h"
#include "SpellCPP.h"
#include "BaseCharacter.h"

void USpellTriggerSpellEffect::ApplyEffect_Implementation(const TArray<ABaseCharacter*>& Characters)
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

	switch (SpawnType) {
	case FSpellTriggerType::SingleSpawn:
	{
		FSpellSpawnParams spawnParams;
		auto SpellData = NewObject<USpellData>(Owner, SpellTrigger);
		SpellData->SpawnSpell(GetWorld(), Caster, Caster, FinalTransform, spawnParams);

		break;
	}
	case FSpellTriggerType::SpawnPerTarget:
	{
		for (auto Character : Characters) {
			FSpellSpawnParams spawnParams;
			spawnParams.Target = Character;
			spawnParams.TargetLocation = Character->GetActorLocation();

			auto SpellData = NewObject<USpellData>(Owner, SpellTrigger);
			SpellData->SpawnSpell(GetWorld(), Caster, Caster, FinalTransform, spawnParams);
		}
		break;
	}
	}
	
}





