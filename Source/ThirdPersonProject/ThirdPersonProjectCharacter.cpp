// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonProject.h"
#include "ActionEvent.h"
#include "ThirdPersonProjectCharacter.h"
#include "MyPlayerState.h"
#include "ThirdPersonProjectGameMode.h"

//////////////////////////////////////////////////////////////////////////
// AThirdPersonProjectCharacter

AThirdPersonProjectCharacter::AThirdPersonProjectCharacter():
	Super()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	//bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	//bUseControllerRotationRoll = false;

	// Configure character movement
	//GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	//GetCharacterMovement()->JumpZVelocity = 600.f;
	//GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	//CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create agro radius component
	AgroRadiusSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroRadius"));
	AgroRadiusSphere->AttachTo(RootComponent);
	AgroRadiusSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AgroRadiusSphere->OnComponentBeginOverlap.AddDynamic(this, &AThirdPersonProjectCharacter::OnAgroRadiusCollision);
	AgroRadiusSphere->IgnoreActorWhenMoving(this, true);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	Energy = 100;
	MaxEnergy = 100;
	Health = 10000;
	MaxHealth = 10000;
	Name = "Metsfan";
	ActiveSpell = NULL;
}

void AThirdPersonProjectCharacter::OnAgroRadiusCollision(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this) {
		AThirdPersonProjectCharacter *character = dynamic_cast<AThirdPersonProjectCharacter *>(OtherActor);
		if (character && !character->InCombat) {
			InCombat = true;
			Target = character;

			this->OnInCombatChanged.Broadcast(this, InCombat);
		}
	}
}

void AThirdPersonProjectCharacter::BeginPlay() {
	Super::BeginPlay();

	AgroRadiusSphere->SetSphereRadius(AgroRadius);
}

void AThirdPersonProjectCharacter::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	EnergyCooloffTime += deltaSeconds;

	if (EnergyCooloffTime >= EnergyCooloff && Energy < MaxEnergy) {
		Energy += EnergyRegenRate * deltaSeconds;
		Energy = FMath::Min(Energy, MaxEnergy);
	}

	if (Controller) {
		//Controller->SetControlRotation(this->GetActorRotation());

		//auto playerState = Cast<AMyPlayerState>(this->Controller->PlayerState);
		//playerState->Update(Cast<ABaseCharacter>(this));
	}
}

bool AThirdPersonProjectCharacter::ExecuteSpell_Validate(UClass* action)
{
	return action != NULL;
}

void AThirdPersonProjectCharacter::ExecuteSpell_Implementation(UClass* action)
{
	if (action) {
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;

		FTransform* transform = new FTransform(FVector(75, 0, 0));

		auto actor = GetWorld()->SpawnActor(action, transform, spawnParams);
		actor->Instigator = this;
		actor->AttachRootComponentToActor(this);

		ActiveSpell = Cast<ASpellCPP>(actor);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AThirdPersonProjectCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAxis("MoveForward", this, &AThirdPersonProjectCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AThirdPersonProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &AThirdPersonProjectCharacter::MouseTurn);
	//InputComponent->BindAxis("TurnRate", this, &AThirdPersonProjectCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &AThirdPersonProjectCharacter::MouseTilt);
	//InputComponent->BindAxis("LookUpRate", this, &AThirdPersonProjectCharacter::LookUpAtRate);

	InputComponent->BindAction("MainAction", IE_Pressed, this, &AThirdPersonProjectCharacter::OnLeftMouseButtonPressed);
	InputComponent->BindAction("MainAction", IE_Released, this, &AThirdPersonProjectCharacter::OnLeftMouseButtonReleased);
}

void AThirdPersonProjectCharacter::OnLeftMouseButtonPressed()
{
	if (MainAction) {
		this->ExecuteSpell(MainAction);
	}
}

void AThirdPersonProjectCharacter::OnLeftMouseButtonReleased()
{
	UActionEvent* args = NewObject<UActionEvent>();
	args->Button = 0;
	args->Type = EActionEvent::AE_Released;

	OnMouseEvent.Broadcast(args);

	/*if (ActiveSpell) {
		ActiveSpell->Finish();
		ActiveSpell = NULL;
	}*/
}

void AThirdPersonProjectCharacter::MouseTurn(float Yaw)
{
	AddControllerYawInput(Yaw);
}


void AThirdPersonProjectCharacter::MouseTilt(float Pitch)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Pitch);
}

void AThirdPersonProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void AThirdPersonProjectCharacter::Jump()
{
	if (Energy >= 20) {
		Super::Jump();

		Energy -= 20;

		EnergyCooloffTime = 0;
		EnergyTickTime = 0;
	}
}

bool AThirdPersonProjectCharacter::CanJumpInternal_Implementation() const
{
	return (GetCharacterMovement()->IsFalling()) || Super::CanJumpInternal_Implementation();
}

void AThirdPersonProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}


void AThirdPersonProjectCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AThirdPersonProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
