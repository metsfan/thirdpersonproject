// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "BaseCharacter.h"
#include "ActionEvent.h"
#include "SpellCPP.h"
#include "Templates/UniquePtr.h"

#include "ThirdPersonProjectCharacter.generated.h"

UENUM()
enum class FSpellAction : uint8 {
	MainAction,
	Spell1,
	Spell2,
	Spell3
};

class UGameHUD;

UCLASS(config=Game)
class AThirdPersonProjectCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	friend class AMainPlayerController;

protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Agro Sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AgroRadiusSphere;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool InCombat;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<ASpellCPP> ActiveSpell;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AThirdPersonProjectCharacter *Target;
	UFUNCTION()
	void OnAgroRadiusCollision(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	AThirdPersonProjectCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Default)
	float AgroRadius;


	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

	void AddHealth_Implementation(int32 delta, ABaseCharacter* Instigator) override;

	USpellData* GetSpell(FSpellAction Action);

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void BeginSprint();
	void EndSprint();

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */

	void MouseTilt(float Pitch);
	void MouseTurn(float Yaw);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void CastSpellAction(FKey Key);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<USpellData> MainAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<USpellData> Spell1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<USpellData> Spell2;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<USpellData> Spell3;

	void Jump() override;

	bool CanJumpInternal_Implementation() const override;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	UFUNCTION(BlueprintCallable, Category = "Default", Server, Reliable, WithValidation)
	void ExecuteSpell(FSpellAction action, const FVector& crosshairPosition);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInCombatChanged, AThirdPersonProjectCharacter *, bool);

	FOnInCombatChanged OnInCombatChanged;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseEvent, class UActionEvent*, Event);

	UPROPERTY(BlueprintAssignable)
		FOnMouseEvent OnMouseEvent;

	

private:
	float EnergyTickTime = 0;

	TMap<FSpellAction, USpellData*> SpellData;

	void OnLeftMouseButtonPressed();
	void OnLeftMouseButtonReleased();

	TMap<FSpellAction, float> SpellCooldown;
	
};

