// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "TextBlockEx.h"

void UTextBlockEx::SetMargin(float left, float bottom, float right, float top)
{
	Margin.Left = left;
	Margin.Bottom = bottom;
	Margin.Right = right;
	Margin.Top = top;

	if (MyTextBlock.IsValid()) {
		this->SynchronizeTextLayoutProperties(*MyTextBlock);
	}
}
