// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "BaseCharacter.h"

#include "SpellEffect.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONPROJECT_API USpellEffect : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellEffect();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Default")
	void ApplyEffect(const TArray<ABaseCharacter*>& Characters);
	virtual void ApplyEffect_Implementation(const TArray<ABaseCharacter*>& Characters);
	
};
