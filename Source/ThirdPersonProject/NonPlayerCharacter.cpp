// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "WidgetLayoutLibrary.h"
#include "NonPlayerCharacter.h"
#include "UnrealNetwork.h"

static const float MaxHealthFrameVisibleTime = 2.0f;

static ConstructorHelpers::FClassFinder<UHealthFrame> *HealthFrameBPClass = NULL;

// Sets default values
ANonPlayerCharacter::ANonPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!HealthFrameBPClass) {
		HealthFrameBPClass = new ConstructorHelpers::FClassFinder<UHealthFrame>(TEXT("/Game/BP_HealthFrame"));
	}
}

// Called when the game starts or when spawned
void ANonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Cast<UHealthFrame>(HealthFrameWidgetComponent->GetUserWidgetObject())->Character = this;
	HealthFrameWidgetComponent->SetVisibility(false);
	HealthFrameWidgetComponent->SetIsReplicated(true);
}

// Called every frame
void ANonPlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (HealthFrameWidgetComponent && HealthFrameWidgetComponent->IsVisible()) {
		HealthFrameVisibleTime += DeltaTime;

		if (HealthFrameVisibleTime >= MaxHealthFrameVisibleTime) {
			HealthFrameWidgetComponent->SetVisibility(false);
		}
	}
}

// Called to bind functionality to input
void ANonPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void ANonPlayerCharacter::AddHealth_Implementation(int32 delta)
{
	Super::AddHealth_Implementation(delta);

	HealthFrameVisibleTime = 0;

	HealthFrameWidgetComponent->SetVisibility(true);
}

void ANonPlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANonPlayerCharacter, HealthFrameWidgetComponent);
	DOREPLIFETIME(ANonPlayerCharacter, HealthFrameVisibleTime);
}