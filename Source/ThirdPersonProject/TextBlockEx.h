// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TextBlock.h"
#include "TextBlockEx.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API UTextBlockEx : public UTextBlock
{
	GENERATED_BODY()


public:
	void SetMargin(float left, float bottom, float right, float top);
};
