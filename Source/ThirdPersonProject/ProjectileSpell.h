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
	
	UPROPERTY(BlueprintReadWrite)
		UProjectileMovementComponent* MovementComponent = NULL;

	UPROPERTY(BlueprintReadWrite)
		UShapeComponent* GeometryComponent = NULL;

protected:
	UFUNCTION()
		virtual void OnGeometryComponentHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
