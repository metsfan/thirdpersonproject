// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "SlashSpell.h"

static ConstructorHelpers::FClassFinder<AActor> *ExplosionEffectBPClass = NULL;

ASlashSpell::ASlashSpell(): Super()
{
	if (!ExplosionEffectBPClass) {
		ExplosionEffectBPClass = new ConstructorHelpers::FClassFinder<AActor>(TEXT("/Game/BP_ExplosionEffect"));
	}
}

void ASlashSpell::BeginPlay()
{
	Super::BeginPlay();

	FTransform transform(this->GetTransform().GetLocation());
	GetWorld()->SpawnActor(ExplosionEffectBPClass->Class, &transform);
}

