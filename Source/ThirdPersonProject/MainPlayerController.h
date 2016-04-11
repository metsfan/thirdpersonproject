// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "ActionEvent.h"
#include "MyPlayerState.h"
#include "MainPlayerController.generated.h"

class ULobbyHUD;
class UGameHUD;
class AThirdPersonProjectCharacter;

UCLASS(Blueprintable)
class THIRDPERSONPROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

	AMainPlayerController();

	virtual void BeginPlay();
	
	virtual void SetPawn(APawn* InPawn) override;
	virtual void Tick(float deltaSeconds) override;

public:
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Nickname)
	FString Nickname;

	UFUNCTION(Server, Reliable, WithValidation)
	void SetNickname(const FString& newNickname);

	void NotifyPlayerJoinedLobby(const TArray<AMyPlayerState*>& players);

	UPROPERTY(BlueprintReadWrite, Replicated)
	bool Ready;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Default")
	void Server_NotifyReady(bool pReady);

	UFUNCTION(Client, Reliable)
	void OnPlayerDied(AMyPlayerState* DeadPlayer);

	virtual void InitPlayerState() override;

	UFUNCTION(Client, Reliable)
	void ClientSetMouseCursorEnabled(bool enabled);

	virtual void OnRep_PlayerState();

	UFUNCTION()
	void OnPlayerAdded(AMyPlayerState* NewPlayer);

	bool IsAlive();

	UGameHUD* GetPlayerHUD() { return PlayerHUD; }

	FVector2D GetCrosshairPosition() { return CrosshairPosition;  }

protected:
	virtual void SetupInputComponent() override;

	UPROPERTY(BlueprintReadWrite)
	ULobbyHUD* LobbyHUDWidget;

	UPROPERTY(BlueprintReadWrite)
	UGameHUD* PlayerHUD;

	UFUNCTION(BlueprintCallable, Category = "Default")
	void OnPostLogin();

	void ShowScore();
	void HideScore();

private:
	UFUNCTION()
	void OnRep_Nickname();

	UFUNCTION(Client, Reliable)
	void ClientOnPlayerDied();

	UFUNCTION()
	void OnPlayerRestartClick();

	UFUNCTION(Server, Reliable, WithValidation)
		void OnPlayerReadyToRestart();

	FVector2D CrosshairPosition;
};
