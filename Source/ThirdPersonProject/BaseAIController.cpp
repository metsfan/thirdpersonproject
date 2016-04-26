// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseCharacter.h"
#include "BaseAIController.h"
#include "NonPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Fireball.h"

static ConstructorHelpers::FClassFinder<ASpellCPP>* FireballBPClass = NULL;

ABaseAIController::ABaseAIController(): Super()
{
	if (!FireballBPClass) {
		FireballBPClass = new ConstructorHelpers::FClassFinder<ASpellCPP>(TEXT("/Game/BP_Fireball"));
	}
}

void ABaseAIController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	auto currentTarget = Cast<ABaseCharacter>(Blackboard->GetValueAsObject("CurrentTarget"));
	if (currentTarget) {
		auto character = Cast<ABaseCharacter>(GetPawn());

		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(character->GetActorLocation(), currentTarget->GetActorLocation());
		rotation.Roll = rotation.Pitch = 0;
		GetPawn()->SetActorRotation(rotation);
	}
}

USpellData* ABaseAIController::GetNextSpell_Implementation()
{
	// A very simple generic spell choosing algorithm: Choose the spell with the longest cooldown that isn't currently on cooldown.

	auto Character = Cast<ANonPlayerCharacter>(GetPawn());
	if (Character) {
		TArray<USpellData*> Spells = Character->GetSpells();
		Spells.Sort([](const USpellData& Spell1, const USpellData& Spell2) -> bool {
			return Spell1.Cooldown > Spell2.Cooldown;
		});
		for (auto Spell : Spells) {
			if (Spell->CooldownRemaining == 0.0f) {
				return Spell;
			}
		}
	}

	return NULL;
}


