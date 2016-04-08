// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "WidgetHelper.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"

FVector2D FWidgetHelper::GetAbsolutePositionForCanvasSlot(UObject* WorldContextObject, UCanvasPanelSlot* CanvasSlot)
{
	auto ViewportSize = UWidgetLayoutLibrary::GetViewportSize(WorldContextObject);
	auto ViewportScale = UWidgetLayoutLibrary::GetViewportScale(WorldContextObject);

	auto AnchorCenter = (CanvasSlot->GetAnchors().Maximum + CanvasSlot->GetAnchors().Minimum) * 0.5;
	auto Position = CanvasSlot->GetPosition() * ViewportScale;
	auto Anchor = AnchorCenter * ViewportSize;
	return Anchor + Position;
}