// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "ProjectileSpell.h"
#include "UnrealNetwork.h"
#include "ThirdPersonProjectCharacter.h"

void AProjectileSpell::BeginPlay()
{
	Super::BeginPlay();

	GeometryComponent->IgnoreActorWhenMoving(this->GetInstigator(), true);
	GeometryComponent->SetIsReplicated(true);

	if (HasAuthority()) {
		GeometryComponent->OnComponentHit.AddDynamic(this, &AProjectileSpell::OnGeometryComponentHit);
	}
}

void AProjectileSpell::OnGeometryComponentHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Role == ROLE_Authority) {
		auto character = dynamic_cast<ABaseCharacter *>(OtherActor);
		if (character) {
			this->ApplyEffects(character);
		}
	}
}

void AProjectileSpell::UpdateProjectileVelocity()
{
	auto rotator = this->GetInstigator()->GetActorRotation().Vector();
	MovementComponent->Velocity = rotator * MovementComponent->InitialSpeed;
}

void AProjectileSpell::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AProjectileSpell, GeometryComponent);
}


bool AProjectileSpell::ServerFinish_Validate()
{
	return true;
}

void AProjectileSpell::ServerFinish_Implementation()
{
	Super::ServerFinish_Implementation();

	
}