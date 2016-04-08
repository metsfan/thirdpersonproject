// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpellCPP.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileSpell.generated.h"

/**
 * A projectile-based spell which has a collision shape and a projectile-based movement.  It will also apply its effects when it collides with a valid target.
 */
UCLASS()
class THIRDPERSONPROJECT_API AProjectileSpell : public ASpellCPP
{
	GENERATED_BODY()
	
public:

	void BeginPlay();
	
	UPROPERTY(BlueprintReadWrite, Replicated)
	UProjectileMovementComponent* MovementComponent = NULL;

	UPROPERTY(BlueprintReadWrite, Replicated)
		UShapeComponent* GeometryComponent = NULL;

	void UpdateProjectileVelocity();

	void StopCollision();

	void SetTargetLocation(const FVector& Location) {
		this->TargetLocation = Location;
	}

	void SetTargetDirection(const FVector& Direction) {
		this->TargetDirection = Direction;
	}

protected:
	
	virtual void OnCollision(class AActor* OtherActor);

	UFUNCTION(Server, Reliable, WithValidation)
		virtual void ServerFinish();

private:
	UFUNCTION()
		void OnGeometryComponentHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnGeometryComponentBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweepTest, const FHitResult& Hit);

	FVector TargetLocation;
	FVector TargetDirection;

};
