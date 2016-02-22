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

	InputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &AMainPlayerController::OnLeftMouseButtonPressed);
	InputComponent->BindAction("LeftMouseButton", IE_Released, this, &AMainPlayerController::OnLeftMouseButtonReleased);
}

void AMainPlayerController::OnLeftMouseButtonPressed()
{
	UActionEvent* args = NewObject<UActionEvent>();
	args->Button = 0;
	args->Type = EActionEvent::AE_Pressed;

	OnMouseEvent.Broadcast(args);
}

void AMainPlayerController::OnLeftMouseButtonReleased()
{
	UActionEvent* args = NewObject<UActionEvent>();
	args->Button = 0;
	args->Type = EActionEvent::AE_Released;

	OnMouseEvent.Broadcast(args);
}


