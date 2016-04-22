// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "FlamestrikeSpell.h"

void AFlamestrikeSpell::OnCollision(class AActor* OtherActor)
{
	Super::OnCollision(OtherActor);

	if (IsValidTarget(OtherActor)) {
		this->Destroy();
	}
}