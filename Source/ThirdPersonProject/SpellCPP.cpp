// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "SpellCPP.h"
#include "ThirdPersonProjectCharacter.h"
#include "DirectDamageSpellEffect.h"
#include "UnrealNetwork.h"

// Sets default values
ASpellCPP::ASpellCPP() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bReplicateMovement = true;
}

// Called when the game starts or when spawned
void ASpellCPP::BeginPlay()
{
	Super::BeginPlay();

	auto effects = this->GetComponentsByClass(USpellEffect::StaticClass());
	for (auto effect : effects) {
		Effects.Add(Cast<USpellEffect>(effect));
	}
}

// Called every frame
void ASpellCPP::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASpellCPP::ApplyEffectsSingle(ABaseCharacter* target)
{
	TArray<ABaseCharacter *> Targets;
	if (target) {
		Targets.Add(target);
	}
	this->ApplyEffectsMulti(Targets);
}

void ASpellCPP::ApplyEffectsMulti(const TArray<ABaseCharacter *>& targets)
{
	for (auto effect : Effects) {
		effect->ApplyEffect(targets);
	}

	if (targets.Num() > 0) {
		for (auto target : targets) {
			target->OnSpellEffectsApplied(this);
		}
	}
}

void ASpellCPP::SetDamageScaleModifier(float modifier)
{
	auto effects = this->GetComponentsByClass(UDirectDamageSpellEffect::StaticClass());
	for (auto effect : effects) {
		auto damageEffect = Cast<UDirectDamageSpellEffect>(effect);
		damageEffect->Damage *= modifier;
	}
}

bool ASpellCPP::ServerFinish_Validate()
{
	return true;
}

void ASpellCPP::ServerFinish_Implementation()
{
	this->Finish();
}

void ASpellCPP::Finish()
{
	if (!HasAuthority()) {
		this->ServerFinish();
	}
}

bool ASpellCPP::IsValidTarget(AActor* target)
{
	if (!target) {
		return false;
	}

	if (target->IsA(ABaseCharacter::StaticClass())) {
		auto targetCharacter = Cast<ABaseCharacter>(target);
		auto ownerCharacter = Cast<ABaseCharacter>(this->GetOwner());
		if (ownerCharacter) {
			if (ownerCharacter == target) {
				return false;
			}

			if (ownerCharacter->TeamID != targetCharacter->TeamID) {
				return TargetType == FTargetType::Enemy || TargetType == FTargetType::All;
			}
			else {
				return TargetType == FTargetType::Friendly || TargetType == FTargetType::All;
			}
		}
		else {
			// If this spell is not owned by a character, then it is owned by the level, in which case we only want it to affect players.
			return targetCharacter->IsPlayerControlled();
		}
	}

	// We'll collide with anything that isn't a character, probably environment geometry
	return true;
}
