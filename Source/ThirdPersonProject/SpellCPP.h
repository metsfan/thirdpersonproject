// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpellEffect.h"
#include "SpellData.h"

#include "SpellCPP.generated.h"

class AThirdPersonProjectCharacter;

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

	void SetDamageScaleModifier(float modifier);

	virtual void Finish();

	FTargetType TargetType;

protected:
	UFUNCTION(BlueprintCallable, Category = "Spell")
	void ApplyEffectsSingle(ABaseCharacter* target);

	UFUNCTION(BlueprintCallable, Category = "Spell")
	void ApplyEffectsMulti(const TArray<ABaseCharacter *>& targets);

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void ServerFinish();
	virtual bool ServerFinish_Validate();
	virtual void ServerFinish_Implementation();
	
	UFUNCTION(BlueprintCallable, Category = "Spell")
	bool IsValidTarget(AActor* target);
	
};
