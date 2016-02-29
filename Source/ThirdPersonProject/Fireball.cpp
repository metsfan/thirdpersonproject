// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "Fireball.h"
#include "ThirdPersonProjectCharacter.h"
#include "ParticleSystems.h"

static UParticleSystem* ExplosionParticles;

static const float kMaxChargeTime = 5.0f;

AFireball::AFireball():
	Super()
{
	ExplosionParticles = UParticleSystems::GetParticleSystem(FString("/Game/StarterContent/Particles"), FString("P_Explosion"));
}

void AFireball::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	if (!MovementComponent->IsActive()) {
		MousePressedTime += deltaSeconds;

		FireScale = FMath::Min(kMaxChargeTime, 1.0f + MousePressedTime);
		if (FireScale == kMaxChargeTime) {
			if (MousePressedTime >= kMaxChargeTime + 1) {
				this->Finish();
			}
		}
		else {
			ParticleSystemComponent->SetRelativeScale3D(FVector(FireScale));
		}
	}
}

AFireball::~AFireball() 
{
	if (GetWorld() && GetWorldTimerManager().TimerExists(ExplosionTimer)) {
		GetWorldTimerManager().ClearTimer(ExplosionTimer);

		auto pc = Cast<AThirdPersonProjectCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());
		pc->OnMouseEvent.RemoveDynamic(this, &AFireball::OnMouseEvent);
	}
}

void AFireball::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent->SetActive(false);
	this->RemoveOwnedComponent(MovementComponent);

	MousePressedTime = 0;
	
	FireScale = 1;

	auto pc = Cast<AThirdPersonProjectCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());
	pc->OnMouseEvent.AddDynamic(this, &AFireball::OnMouseEvent);
}

void AFireball::OnMouseEvent(UActionEvent* args)
{
	if (args->Type == EActionEvent::AE_Released) {
		this->Finish();
	}
}

void AFireball::Finish()
{
	MovementComponent->SetActive(true);
	this->AddOwnedComponent(MovementComponent);
	this->UpdateProjectileVelocity();

	this->SetDamageScaleModifier(FMath::Pow(FireScale, 2));
}

void AFireball::OnGeometryComponentHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnGeometryComponentHit(OtherActor, OtherComp, NormalImpulse, Hit);

	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([this] {
		this->Destroy();
	});

	GetWorldTimerManager().SetTimer(ExplosionTimer, TimerCallback, 1.0, false, 1.0);

	ParticleSystemComponent->SetTemplate(ExplosionParticles);
}