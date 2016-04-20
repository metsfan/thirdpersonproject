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

UCLASS(meta = (BlueprintSpawnableComponent))
class THIRDPERSONPROJECT_API USpellTriggerSpellEffect : public USpellEffect
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "Default")
		virtual void ApplyEffect(TArray<ABaseCharacter*> characters);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<USpellData> SpellTrigger;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FSpellTriggerLocation SpawnLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform SpawnTransform;
};
