// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "PulseAreaEffectSpell.h"

void APulseAreaEffectSpell::BeginPlay()
{
	Super::BeginPlay();

	if (Role == ROLE_Authority) {
		AreaShapeComponent->OnComponentEndOverlap.AddDynamic(this, &APulseAreaEffectSpell::OnAreaEndOverlap);
	}
}

void APulseAreaEffectSpell::OnAreaBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweepTest, const FHitResult& Hit)
{
	auto Character = Cast<ABaseCharacter>(OtherActor);
	if (Character && this->IsValidTarget(OtherActor)) {
		OverlappingTargets.Add(Character);
	}
}

void APulseAreaEffectSpell::OnAreaEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Character = Cast<ABaseCharacter>(OtherActor);
	if (Character) {
		OverlappingTargets.Remove(Character);
	}
}

void APulseAreaEffectSpell::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TotalTime += DeltaSeconds;

	if (TotalTime > PulseDelay) {
		TimeSincePulse += DeltaSeconds;

		if (TimeSincePulse >= PulseTime) {
			TimeSincePulse = 0;

			this->ApplyEffectsMulti(OverlappingTargets);
		}
	}
}