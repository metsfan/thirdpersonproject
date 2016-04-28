// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "AreaEffectSpell.h"

void AAreaEffectSpell::BeginPlay()
{
	Super::BeginPlay();

	if (Role == ROLE_Authority) {
		AreaShapeComponent->OnComponentBeginOverlap.AddDynamic(this, &AAreaEffectSpell::OnAreaBeginOverlap);
	}
}

void AAreaEffectSpell::OnAreaBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweepTest, const FHitResult& Hit)
{
	if (Role == ROLE_Authority) {
		auto character = Cast<ABaseCharacter>(OtherActor);
		if (character && this->IsValidTarget(character)) {
			this->ApplyEffectsSingle(character);
		}
	}
}


