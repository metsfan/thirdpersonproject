// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "HomingProjectileSpell.h"

void AHomingProjectileSpell::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Target.Get()) {
		this->SetTargetLocation(Target->GetActorLocation());
		this->UpdateProjectileVelocity();
	}
}