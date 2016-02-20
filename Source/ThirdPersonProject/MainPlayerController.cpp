// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "MainPlayerController.h"

void AMainPlayerController::BeginPlay()
{
	APlayerController::BeginPlay();
}

void AMainPlayerController::SetupInputComponent()
{
	InputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &AMainPlayerController::OnLeftMouseButtonPressed);
	InputComponent->BindAction("LeftMouseButton", IE_Released, this, &AMainPlayerController::OnReleasedMouseButtonPressed);
}

void AMainPlayerController::OnLeftMouseButtonPressed()
{

}

void OnLeftMouseButtonReleased()
{

}


