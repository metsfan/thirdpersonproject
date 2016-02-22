// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "ParticleSystems.h"

struct ParticleSystemPath
{
	FString name;
	FString path;

	ParticleSystemPath(const FString& _path, const FString& _name) :
		name(_name), path(_path)
	{}
};

static UParticleSystems* sInstance = nullptr;

static TArray<ParticleSystemPath> sParticleSystemPaths =
TArrayBuilder<ParticleSystemPath>()
.Add(ParticleSystemPath(FString("/Game/StarterContent/Particles"), FString("P_Explosion")))
.Build();

UParticleSystems::UParticleSystems():
	Super()
{
	for (auto& system : sParticleSystemPaths) {
		auto formattedPath = FString::Printf(TEXT("ParticleSystem'%s/%s.%s'"), *system.path, *system.name, *system.name);
		auto fObject = ConstructorHelpers::FObjectFinder<UParticleSystem>(*formattedPath);
		if (fObject.Object != nullptr) {
			ParticleSystems.Add(system.name, fObject.Object);
		}
	}
	
}

UParticleSystems * UParticleSystems::GetInstance()
{
	if (sInstance == nullptr) {
		sInstance = NewObject<UParticleSystems>();
	}

	return sInstance;
}

UParticleSystem* UParticleSystems::GetParticleSystem(const FString& path, const FString& name)
{
	auto formattedPath = FString::Printf(TEXT("ParticleSystem'%s/%s.%s'"), *path, *name, *name);
	auto fObject = ConstructorHelpers::FObjectFinder<UParticleSystem>(*formattedPath);

	return fObject.Object;
}




