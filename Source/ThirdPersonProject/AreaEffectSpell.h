// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpellCPP.h"
#include "AreaEffectSpell.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API AAreaEffectSpell : public ASpellCPP
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(BlueprintReadWrite)
	UShapeComponent* AreaShapeComponent;
	
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	virtual void OnAreaBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweepTest, const FHitResult& Hit);
};
