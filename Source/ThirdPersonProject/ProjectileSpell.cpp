// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "ProjectileSpell.h"
#include "UnrealNetwork.h"
#include "ThirdPersonProjectCharacter.h"
#include "BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"

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

void AProjectileSpell::OnCollision_Implementation(class AActor* OtherActor)
{
	if (Role == ROLE_Authority) {
		auto character = Cast<ABaseCharacter>(OtherActor);
		if (this->IsValidTarget(OtherActor)) {
			this->ApplyEffectsSingle(character);
		}
	}

	if (DestroyOnValidCollision && this->IsValidTarget(OtherActor)) {
		this->Destroy();
	}
}

void AProjectileSpell::UpdateProjectileVelocity()
{
	auto character = Cast<ABaseCharacter>(this->GetInstigator());
	if (character && character->Controller) {
		FVector rotator;
		FVector characterRotation = character->Controller->GetControlRotation().Vector();

		if (TargetDirection != FVector(0)) {
			rotator = TargetDirection;
		} 
		else if (TargetLocation != FVector(0)) {
			auto position = character->GetActorLocation();
			rotator = UKismetMathLibrary::FindLookAtRotation(position, TargetLocation).Vector();
		}
		else {
			rotator = characterRotation;
		}

		MovementComponent->Velocity = rotator * MovementComponent->InitialSpeed;
	}
}

void AProjectileSpell::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AProjectileSpell, GeometryComponent);
	DOREPLIFETIME(AProjectileSpell, DestroyOnValidCollision);
}

void AProjectileSpell::Finish() {
	Super::Finish();

	MovementComponent->SetActive(true);
	this->UpdateProjectileVelocity();
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