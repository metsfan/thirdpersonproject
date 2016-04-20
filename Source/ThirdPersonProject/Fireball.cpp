// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "Fireball.h"
#include "ThirdPersonProjectCharacter.h"
#include "ParticleSystems.h"
#include "ThirdPersonProjectGameMode.h"
#include "UnrealNetwork.h"

static UParticleSystem* ExplosionParticles;

static ConstructorHelpers::FClassFinder<AActor> *ExplosionEffectBPClass = NULL;

static const float kMaxChargeTime = 5.0f;

AFireball::AFireball():
	Super()
{
	ExplosionParticles = UParticleSystems::GetParticleSystem(FString("/Game/StarterContent/Particles"), FString("P_Explosion"));

	if (!ExplosionEffectBPClass) {
		ExplosionEffectBPClass = new ConstructorHelpers::FClassFinder<AActor>(TEXT("/Game/BP_ExplosionEffect"));
	}
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
	if (GetWorld()) {
		GetWorldTimerManager().ClearTimer(ExplosionTimer);
	}
}

void AFireball::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent->SetActive(false);

	MousePressedTime = 0;
	
	FireScale = 1;

	ParticleSystemComponent->SetIsReplicated(true);

	if (GetGameInstance()->GetFirstLocalPlayerController() != NULL) {
		//auto inputManager = UInputEventManager::Get();
		auto pc = Cast<AThirdPersonProjectCharacter>(GetOwner());
		if (pc && pc->IsLocallyControlled()) {
			pc->OnMouseEvent.AddDynamic(this, &AFireball::OnMouseEvent);
		}
	}
}

void AFireball::OnMouseEvent(UActionEvent* args)
{
	if (args->Type == EActionEvent::AE_Released) {
		this->SetTargetLocation(args->CrosshairPosition);
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

	if (FireScale > 2) {
		this->SetDamageScaleModifier(FMath::Pow(FireScale, 1.1));
	}

	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([this] {
		this->ShowExplosionEffect();

		this->Destroy();
	});

	GetWorldTimerManager().SetTimer(ExplosionTimer, TimerCallback, 0.0, false, 3.0);

	this->DetachRootComponentFromParent();

	UE_LOG(MyLog, Log, TEXT("Shooting Fireball animation on machine with role: %d"), (int32)Role.GetValue())
}

void AFireball::OnCollision(class AActor* OtherActor)
{
	Super::OnCollision(OtherActor);

	if (this->IsValidTarget(OtherActor)) {
		StopCollision();


		//GetWorldTimerManager().SetTimer(ExplosionTimer, TimerCallback, 1.0, false, 1.0);

		this->ShowExplosionEffect();

		this->Destroy();

		GetWorldTimerManager().ClearTimer(ExplosionTimer);
	}
	//UE_LOG(MyLog, Log, TEXT("Showing Fireball animation on machine with role: %d"), (int32) Role.GetValue());
}

void AFireball::ShowExplosionEffect()
{
	//ParticleSystemComponent->SetTemplate(ExplosionParticles);
	FTransform transform(this->GetTransform().GetLocation());
	GetWorld()->SpawnActor(ExplosionEffectBPClass->Class, &transform);
}

void AFireball::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFireball, ParticleSystemComponent);
}
