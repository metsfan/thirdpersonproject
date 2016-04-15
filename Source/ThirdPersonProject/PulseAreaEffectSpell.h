// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AreaEffectSpell.h"
#include "PulseAreaEffectSpell.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API APulseAreaEffectSpell : public AAreaEffectSpell
{
	GENERATED_BODY()
	
protected:
	TArray<ABaseCharacter*> OverlappingTargets;

	UFUNCTION()
	virtual void OnAreaBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweepTest, const FHitResult& Hit) override;

	UFUNCTION()
	virtual void OnAreaEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PulseTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PulseDelay;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	float TotalTime;
	float TimeSincePulse;
};
