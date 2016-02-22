// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "ActionEvent.h"
#include "MainPlayerController.generated.h"


UCLASS(Blueprintable)
class THIRDPERSONPROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()


		virtual void BeginPlay();
	
public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseEvent, class UActionEvent*, Event);

	UPROPERTY(BlueprintAssignable)
	FOnMouseEvent OnMouseEvent;

protected:
	virtual void SetupInputComponent() override;

private:
	void OnLeftMouseButtonPressed();
	void OnLeftMouseButtonReleased();
};
