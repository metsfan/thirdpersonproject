// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "GameHUD.h"

void UGameHUD::NativeConstruct()
{
	Super::Construct();

	PlayerFrameWidget->Player = Cast<AThirdPersonProjectCharacter>(GetOwningPlayer()->GetPawn());
}



