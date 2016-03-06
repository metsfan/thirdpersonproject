// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "ProjectileSpell.h"
#include "UnrealNetwork.h"
#include "ThirdPersonProjectCharacter.h"
#include "BaseCharacter.h"

void AProjectileSpell::BeginPlay()
{
	Super::BeginPlay();

	GeometryComponent->IgnoreActorWhenMoving(this->GetInstigator(), true);
	GeometryComponent->SetIsReplicated(true);

	if (HasAuthority()) {
		GeometryComponent->OnComponentHit.AddDynamic(this, &AProjectileSpell::OnGeometryComponentHit);
		GeometryComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileSpell::OnGeometryComponentBeginOverlap);
	}
}

void AProjectileSpell::OnGeometryComponentHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	this->OnCollision(OtherActor);
}

void AProjectileSpell::OnGeometryComponentBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweepTest, const FHitResult& Hit)
{
	this->OnCollision(OtherActor);
}

void AProjectileSpell::OnCollision(class AActor* OtherActor)
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
	auto character = Cast<ABaseCharacter>(this->GetInstigator());
	auto rotator = character->Controller->GetControlRotation().Vector();
	MovementComponent->Velocity = rotator * MovementComponent->InitialSpeed;
}

void AProjectileSpell::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AProjectileSpell, GeometryComponent);
}

void AProjectileSpell::StopCollision()
{
	GeometryComponent->OnComponentHit.RemoveDynamic(this, &AProjectileSpell::OnGeometryComponentHit);
}

bool AProjectileSpell::ServerFinish_Validate()
{
	return true;
}

void AProjectileSpell::ServerFinish_Implementation()
{
	Super::ServerFinish_Implementation();

	
}