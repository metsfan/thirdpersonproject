// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpellEffect.h"
#include "SpellData.h"

#include "SpellCPP.generated.h"

class AThirdPersonProjectCharacter;

UENUM()
enum class FTargetType : uint8 {
	EnemyOnly,
	FriendlyOnly,
	EnemyAndFriendly
};

UCLASS()
class THIRDPERSONPROJECT_API ASpellCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpellCPP();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(BlueprintReadWrite)
		TArray<USpellEffect *> Effects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USpellData* Data;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FTargetType TargetType;

	void SetDamageScaleModifier(float modifier);

	virtual void Finish();

protected:

	virtual void ApplyEffects(ABaseCharacter* target);
	virtual void ApplyEffects(const TArray<ABaseCharacter *>& targets);

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void ServerFinish();
	virtual bool ServerFinish_Validate();
	virtual void ServerFinish_Implementation();
	
	bool IsValidTarget(AActor* target);
	
};
