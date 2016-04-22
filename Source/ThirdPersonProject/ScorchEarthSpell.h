// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpellCPP.h"
#include "ScorchEarthSpell.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API AScorchEarthSpell : public ASpellCPP
{
	GENERATED_BODY()

public:
	AScorchEarthSpell();
	~AScorchEarthSpell();
	
	virtual void BeginPlay() override;

	void TimerTick();

private:
	FTimerHandle Timer;
};
