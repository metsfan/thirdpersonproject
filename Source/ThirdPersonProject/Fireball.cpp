// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "Fireball.h"
#include "ThirdPersonProjectCharacter.h"
#include "ParticleSystems.h"
#include "ThirdPersonProjectGameMode.h"
#include "UnrealNetwork.h"

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

		//auto inputManager = UInputEventManager::Get();
		//inputManager->OnMouseEvent.RemoveDynamic(this, &AFireball::OnMouseEvent);
	}
}

void AFireball::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent->SetActive(false);
	this->RemoveOwnedComponent(MovementComponent);

	MousePressedTime = 0;
	
	FireScale = 1;

	ParticleSystemComponent->SetIsReplicated(true);

	if (GetGameInstance()->GetFirstLocalPlayerController() != NULL) {
		//auto inputManager = UInputEventManager::Get();
		auto pc = Cast<AThirdPersonProjectCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());
		pc->OnMouseEvent.AddDynamic(this, &AFireball::OnMouseEvent);
	}
}

void AFireball::OnMouseEvent(UActionEvent* args)
{
	if (args->Type == EActionEvent::AE_Released) {
		this->Finish();
	}
}

/*bool AFireball::Finish_Validate()
{
	return true;
}
*/
void AFireball::Finish()
{
	Super::Finish();

	MovementComponent->SetActive(true);
	this->AddOwnedComponent(MovementComponent);
	this->UpdateProjectileVelocity();

	if (FireScale > 2) {
		this->SetDamageScaleModifier(FMath::Pow(FireScale, 1.1));
	}
}

void AFireball::OnGeometryComponentHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnGeometryComponentHit(OtherActor, OtherComp, NormalImpulse, Hit);

	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([this] {
		this->Destroy();
	});

	GetWorldTimerManager().SetTimer(ExplosionTimer, TimerCallback, 1.0, false, 1.0);

	this->ShowExplosionEffect();

	UE_LOG(MyLog, Log, TEXT("Showing Fireball animation on machine with role: %d"), (int32) Role.GetValue());
}

void AFireball::ShowExplosionEffect_Implementation()
{
	ParticleSystemComponent->SetTemplate(ExplosionParticles);
}

void AFireball::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFireball, ParticleSystemComponent);
}
