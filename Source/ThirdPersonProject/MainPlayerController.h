// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "ActionEvent.h"
#include "MainPlayerController.generated.h"

class ULobbyHUD;

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

	UFUNCTION(NetMulticast, Reliable)
	void NotifyPlayerJoinedLobby();

	UPROPERTY(BlueprintReadWrite, Replicated)
	bool Ready;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Default")
	void Server_NotifyReady(bool pReady);

protected:
	virtual void SetupInputComponent() override;

	UPROPERTY(BlueprintReadWrite)
	ULobbyHUD* LobbyHUDWidget;

private:
	UFUNCTION()
	void OnRep_Nickname();
};
