// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "SpellEffect.h"


// Sets default values for this component's properties
USpellEffect::USpellEffect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpellEffect::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USpellEffect::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void USpellEffect::ApplyEffect(TArray<ABaseCharacter*> characters)
{
}

