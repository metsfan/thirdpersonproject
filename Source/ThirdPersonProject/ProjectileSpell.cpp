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
	auto character = dynamic_cast<ABaseCharacter *>(OtherActor);
	if (character) {
		this->ApplyEffects(character);
	}
}

void AProjectileSpell::UpdateProjectileVelocity()
{
	auto rotator = this->GetInstigator()->GetActorForwardVector();
	MovementComponent->Velocity = rotator * MovementComponent->InitialSpeed;
}