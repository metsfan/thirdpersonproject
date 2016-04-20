// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "ActionEvent.generated.h"

UENUM(BlueprintType)
enum class EActionEvent : uint8
{
	AE_Pressed UMETA(DisplayName="Pressed"),
	AE_Released UMETA(DisplayName = "Released")
};

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API UActionEvent : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	EActionEvent Type;

	UPROPERTY(BlueprintReadOnly)
	int32 Button;

	UPROPERTY(BlueprintReadOnly)
	FVector CrosshairPosition;
	
};
