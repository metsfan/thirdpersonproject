// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpellEffect.h"
#include "SpellData.h"
#include "SpellTriggerSpellEffect.generated.h"

/**
 * 
 */
UENUM()
enum class FSpellTriggerLocation : uint8 {
	RelativeToSelfLocation,
	RelativeToOwnerLocation,
	RelativeToWorld
};

UENUM()
enum class FSpellTriggerType : uint8 {
	SingleSpawn,
	SpawnPerTarget
};

UCLASS(meta = (BlueprintSpawnableComponent))
class THIRDPERSONPROJECT_API USpellTriggerSpellEffect : public USpellEffect
{
	GENERATED_BODY()


public:
	virtual void ApplyEffect_Implementation(const TArray<ABaseCharacter*>& Characters);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<USpellData> SpellTrigger;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FSpellTriggerLocation SpawnLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FSpellTriggerType SpawnType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform SpawnTransform;
};
