// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "Fireball.h"
#include "ParticleSystems.h"

static UParticleSystem* ExplosionParticles;

AFireball::AFireball():
	Super()
{
	ExplosionParticles = UParticleSystems::GetParticleSystem(FString("P_Explosion"));
}

void AFireball::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
}


void AFireball::BeginPlay()
{
	Super::BeginPlay();
}

void AFireball::OnGeometryComponentHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnGeometryComponentHit(OtherActor, OtherComp, NormalImpulse, Hit);

	//GetWorldTimerManager().SetTimer(ExplosionTimer, this, )
	ParticleSystemComponent->SetTemplate(ExplosionParticles);
}