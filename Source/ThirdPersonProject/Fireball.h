// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectileSpell.h"

#include "Particles/ParticleSystemComponent.h"
#include "MainPlayerController.h"

#include "Fireball.generated.h"



/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API AFireball : public AProjectileSpell
{
	GENERATED_BODY()

	AFireball();
	~AFireball();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;
	
	
protected:
	UPROPERTY(BlueprintReadWrite, Replicated)
		UParticleSystemComponent* ParticleSystemComponent;

	FTimerHandle ExplosionTimer;


	void OnGeometryComponentHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void Finish() override;

private:
	UFUNCTION()
	void OnMouseEvent(UActionEvent* args);

	UFUNCTION(NetMulticast, Unreliable)
	void ShowExplosionEffect();

	float MousePressedTime;
	float FireScale;
	
};
