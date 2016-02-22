// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpellEffect.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;

	

	UPROPERTY(BlueprintReadWrite)
		TArray<USpellEffect *> Effects;

	void SetDamageScaleModifier(float modifier);


protected:
	virtual void ApplyEffects(AThirdPersonProjectCharacter* target);
	virtual void ApplyEffects(TArray<AThirdPersonProjectCharacter *> targets);

	
	
};
