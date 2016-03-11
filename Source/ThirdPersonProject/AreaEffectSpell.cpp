// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "AreaEffectSpell.h"

void AAreaEffectSpell::BeginPlay()
{
	Super::BeginPlay();

	TArray<FOverlapResult> results;
	FCollisionShape shape = AreaShapeComponent->GetCollisionShape();
	FVector position = AreaShapeComponent->ComponentToWorld.GetTranslation();

	const FRotator rotation = AreaShapeComponent->ComponentToWorld.Rotator();

	GetWorld()->OverlapMultiByObjectType(results, position, rotation.Quaternion(), FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), shape);

	TArray<ABaseCharacter *> Targets;
	for (auto& result : results) {
		auto character = Cast<ABaseCharacter>(result.Actor.Get());
		if (character) {
			Targets.Add(character);
		}
	}

	this->ApplyEffects(Targets);

	FTimerDelegate destroyCallback;
	destroyCallback.BindLambda([this]() {
		this->Destroy();
	});
	FTimerHandle timerHandle;

	GetWorldTimerManager().SetTimer(timerHandle, destroyCallback, 0.0f, false, 1.0f);
}

void AAreaEffectSpell::OnAreaBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweepTest, const FHitResult& Hit)
{
	if (Role == ROLE_Authority) {
		auto character = Cast<ABaseCharacter>(OtherActor);
		if (character) {
			this->ApplyEffects(character);
		}
	}

	this->Destroy();
}


