// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "ProjectileSpell.h"

#include "ThirdPersonProjectCharacter.h"

void AProjectileSpell::BeginPlay()
{
	Super::BeginPlay();

	GeometryComponent->IgnoreActorWhenMoving(this->GetInstigator(), true);

	GeometryComponent->OnComponentHit.AddDynamic(this, &AProjectileSpell::OnGeometryComponentHit);
}

void AProjectileSpell::OnGeometryComponentHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto thirdPersonCharacter = dynamic_cast<AThirdPersonProjectCharacter *>(OtherActor);
	if (thirdPersonCharacter) {
		this->ApplyEffects(thirdPersonCharacter);
	}
}