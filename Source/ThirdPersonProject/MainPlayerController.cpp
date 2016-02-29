// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "MainPlayerController.h"
#include "ActionEvent.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &AMainPlayerController::OnLeftMouseButtonPressed);
	//InputComponent->BindAction("LeftMouseButton", IE_Released, this, &AMainPlayerController::OnLeftMouseButtonReleased);
}

