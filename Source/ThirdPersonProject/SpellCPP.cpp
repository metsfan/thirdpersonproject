// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "SpellCPP.h"
#include "ThirdPersonProjectCharacter.h"
#include "DirectDamageSpellEffect.h"

// Sets default values
ASpellCPP::ASpellCPP()
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

void ASpellCPP::ApplyEffects(ABaseCharacter* target)
{
	this->ApplyEffects(TArrayBuilder<ABaseCharacter *>().Add(target).Build());
}

bool ASpellCPP::ApplyEffects_Validate(const TArray<ABaseCharacter *>& targets)
{
	return true;
}

void ASpellCPP::ApplyEffects_Implementation(const TArray<ABaseCharacter *>& targets)
{

	for (auto effect : Effects) {
		effect->ApplyEffect(targets);
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

