// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "SpellData.h"
#include "SpellCPP.h"
#include "ProjectileSpell.h"
#include "HomingProjectileSpell.h"

ASpellCPP* USpellData::SpawnSpell(UWorld* World, AActor* Owner, APawn* Instigator, const FTransform& Transform, const FSpellSpawnParams& SpawnParams)
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = Owner;
	spawnParams.Instigator = Instigator;

	FTransform FinalTransform = Transform;
	if (SpawnRelativeToParent) {
		FinalTransform = Owner->GetTransform() * Transform;
	}

	auto Spell = Cast<ASpellCPP>(World->SpawnActor(Class, &FinalTransform, spawnParams));
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