// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "SpellData.generated.h"

UENUM()
enum class FTargetType : uint8 {
	Enemy,
	Friendly,
	All
};

/**
 * 
 */
class ASpellCPP;

UCLASS(Blueprintable)
class THIRDPERSONPROJECT_API USpellData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MaxRange;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MinRange;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Cooldown;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<ASpellCPP> Class;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<FTargetType> TargetType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Duration;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* Icon;

	UPROPERTY(BlueprintReadOnly)
		float CooldownRemaining;

	UPROPERTY(BlueprintReadOnly)
		FKey Hotkey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool AttachToParent;

	ASpellCPP* SpawnSpell(UWorld* World, AActor* Owner, APawn* Instigator, const FTransform& Transform);

};
