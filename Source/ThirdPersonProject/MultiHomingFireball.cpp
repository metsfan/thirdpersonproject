// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "MultiHomingFireball.h"
#include "BaseCharacter.h"

void AMultiHomingFireball::BeginPlay()
{
	Super::BeginPlay();

	auto Owner = Cast<ABaseCharacter>(this->GetOwner());

	TArray<ABaseCharacter*> Targets;
	for (TActorIterator<ABaseCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		auto Actor = *ActorItr;
		if (Actor->TeamID != Owner->TeamID) {
			Targets.Add(Actor);
		}
	}

	this->ApplyEffectsMulti(Targets);

	this->Destroy();
}

