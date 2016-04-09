// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AIController.h"
#include "BaseCharacter.h"
#include "HealthFrame.h"
#include "Components/WidgetComponent.h"
#include "Components/CanvasPanel.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NonPlayerCharacter.generated.h"

UCLASS()
class THIRDPERSONPROJECT_API ANonPlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANonPlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(BlueprintReadWrite)
		AAIController* AIController;

	UPROPERTY(BlueprintReadWrite, Replicated)
		UWidgetComponent* HealthFrameWidgetComponent;

	virtual void AddHealth_Implementation(int32 delta, ABaseCharacter* InstigatorCharacter) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void OnSpellEffectsApplied(ASpellCPP* Spell) override;

private:
	UCanvasPanelSlot* CanvasSlot;

	UPROPERTY(Replicated)
	float HealthFrameVisibleTime = 0;

	TSet<int32> DamagingPlayers;
};
