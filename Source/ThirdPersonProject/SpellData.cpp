// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "SpellData.h"
#include "SpellCPP.h"
#include "ProjectileSpell.h"
#include "HomingProjectileSpell.h"

ASpellCPP* USpellData::SpawnSpell(UObject* WorldContextObject, AActor* Owner, APawn* Instigator, const FTransform& Transform, const FSpellSpawnParams& SpawnParams)
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = Owner;
	spawnParams.Instigator = Instigator;

	FTransform FinalTransform = Transform;
	if (SpawnRelativeToParent) {
		FinalTransform = Transform * Owner->GetTransform();
	}

	auto Spell = Cast<ASpellCPP>(WorldContextObject->GetWorld()->SpawnActor(Class, &FinalTransform, spawnParams));
	if (Spell) {
		if (AttachToParent) {
			Spell->AttachRootComponentToActor(Owner);
		}
		Spell->TargetType = TargetType;
		if (Duration > 0) {
			Spell->SetLifeSpan(Duration);
		}

		if (Spell->IsA(AProjectileSpell::StaticClass())) {
			auto Projectile = Cast<AProjectileSpell>(Spell);
			Projectile->SetTargetLocation(SpawnParams.TargetLocation);
			Projectile->UpdateProjectileVelocity();

			if (Spell->IsA(AHomingProjectileSpell::StaticClass())) {
				auto HomingProjectile = Cast<AHomingProjectileSpell>(Spell);
				HomingProjectile->Target = SpawnParams.Target;
				HomingProjectile->SetTargetLocation(SpawnParams.Target->GetActorLocation());
			}
		}
	}

	CooldownRemaining = Cooldown;

	return Spell;
}

ASpellCPP* USpellData::SpawnSpellOfType(UObject* WorldContextObject, TSubclassOf<USpellData> Type, AActor* Owner, APawn* Instigator, const FTransform& Transform, const FSpellSpawnParams& SpawnParams)
{
	auto SpellData = NewObject<USpellData>(WorldContextObject, Type);
	return SpellData->SpawnSpell(WorldContextObject, Owner, Instigator, Transform, SpawnParams);
}