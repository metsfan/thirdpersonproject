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

AFireball::~AFireball() 
{
	if (GetWorld() && GetWorldTimerManager().TimerExists(ExplosionTimer)) {
		GetWorldTimerManager().ClearTimer(ExplosionTimer);
	}
}

void AFireball::BeginPlay()
{
	Super::BeginPlay();
}

void AFireball::OnGeometryComponentHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnGeometryComponentHit(OtherActor, OtherComp, NormalImpulse, Hit);

	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([this] {
		this->Destroy();
	});

	GetWorldTimerManager().SetTimer(ExplosionTimer, TimerCallback, 1.0, false, 1.0);

	ParticleSystemComponent->SetTemplate(ExplosionParticles);
}