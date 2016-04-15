// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "WidgetLayoutLibrary.h"
#include "NonPlayerCharacter.h"
#include "UnrealNetwork.h"
#include "ThirdPersonProjectCharacter.h"
#include "MainGameState.h"
#include "MyPlayerState.h"

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

	HealthFrameWidgetComponent->SetVisibility(false);
	HealthFrameWidgetComponent->SetIsReplicated(true);
}

// Called every frame
void ANonPlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (HealthFrameWidgetComponent) {
		if (HealthFrameWidgetComponent->GetUserWidgetObject()) {
			auto WidgetObject = Cast<UHealthFrame>(HealthFrameWidgetComponent->GetUserWidgetObject());
			if (!WidgetObject->Character) {
				WidgetObject->Character = this;
			}
		}
	}

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

void ANonPlayerCharacter::AddHealth_Implementation(int32 delta, ABaseCharacter* InstigatorCharacter)
{
	Super::AddHealth_Implementation(delta, InstigatorCharacter);

	HealthFrameVisibleTime = 0;

	HealthFrameWidgetComponent->SetVisibility(true);

	auto Player = Cast<AThirdPersonProjectCharacter>(InstigatorCharacter);
	if (Player && Player->Controller && Player->Controller->PlayerState && TeamID != Player->TeamID) {
		auto PlayerState = Cast<AMyPlayerState>(Player->Controller->PlayerState);

		if (delta < 0) {
			PlayerState->DamageDone += delta * -1;
		}
	}
}

void ANonPlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANonPlayerCharacter, HealthFrameWidgetComponent);
	DOREPLIFETIME(ANonPlayerCharacter, HealthFrameVisibleTime);
}

void ANonPlayerCharacter::OnSpellEffectsApplied(ASpellCPP* Spell)
{
	auto Player = Cast<AThirdPersonProjectCharacter>(Spell->GetNetOwner());
	auto GameState = Cast<AMainGameState>(GetWorld()->GetGameState());
	if (Player && Player->Controller && Player->Controller->PlayerState && TeamID != Player->TeamID) {
		// Owner is a player, and its not friendly, so this is an enemy spell hit
		int32 PlayerId = Player->Controller->PlayerState->PlayerId;
		if (this->IsAlive()) {
			DamagingPlayers.Add(PlayerId);
		}
		else {
			// Track kill for player
			GameState->TrackKill(PlayerId);

			// Track assist for all other players
			DamagingPlayers.Remove(PlayerId); // Remove this player just to be sure

			for (int32 PlayerId : DamagingPlayers) {
				GameState->TrackAssist(PlayerId);
			}
		}
	}
}