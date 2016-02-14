// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "SpellCPP.h"
#include "ThirdPersonProjectCharacter.h"

// Sets default values
ASpellCPP::ASpellCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void ASpellCPP::ApplyEffects(AThirdPersonProjectCharacter* target)
{
	this->ApplyEffects(TArrayBuilder<AThirdPersonProjectCharacter *>().Add(target).Build());
}

void ASpellCPP::ApplyEffects(TArray<AThirdPersonProjectCharacter *> targets)
{
	for (auto effect : Effects) {
		effect->ApplyEffect(targets);
	}
}
