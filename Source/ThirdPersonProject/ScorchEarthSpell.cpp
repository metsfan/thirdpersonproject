// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "ScorchEarthSpell.h"
#include "SpellData.h"

static ConstructorHelpers::FClassFinder<USpellData> *EffectBPClass = NULL;

AScorchEarthSpell::AScorchEarthSpell(): Super()
{
	if (!EffectBPClass) {
		EffectBPClass = new ConstructorHelpers::FClassFinder<USpellData>(TEXT("/Game/BP_ScorchEarthGroundEffectData"));
	}
}

AScorchEarthSpell::~AScorchEarthSpell()
{
	if (GetWorld()) {
		GetWorldTimerManager().ClearTimer(Timer);
	}
}

void AScorchEarthSpell::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(Timer, this, &AScorchEarthSpell::TimerTick, 0.5, true);
}

void AScorchEarthSpell::TimerTick()
{
	auto TraceStart = this->GetActorLocation();
	auto TraceEnd = TraceStart + (FVector(0, 0, -1) * 1000);

	FCollisionQueryParams TraceParams;

	FHitResult OutHit;
	GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, ECollisionChannel::ECC_WorldStatic, TraceParams);

	if (OutHit.Actor.IsValid()) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;

		FTransform transform(OutHit.Location);

		auto ActionData = NewObject<USpellData>(this, EffectBPClass->Class);
		auto actor = Cast<ASpellCPP>(GetWorld()->SpawnActor(ActionData->Class, &transform, spawnParams));
		if (actor) {
			actor->TargetType = ActionData->TargetType;
			if (ActionData->Duration > 0) {
				actor->SetLifeSpan(ActionData->Duration);
			}

			ActionData->CooldownRemaining = ActionData->Cooldown;
		}
	}
}
