// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "ScoreOverlay.h"
#include "Components/TextBlock.h"

void UScoreOverlay::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	auto GameState = GetWorld()->GetGameState<AMainGameState>();

	if (GameState) {
		if (GameState->ConnectedPlayersArray != ConnectedPlayers) {
			ConnectedPlayers = GameState->ConnectedPlayersArray;

			this->UpdateScoreTable();
		}
	}
}

void UScoreOverlay::UpdateScoreTable()
{
	GridWidget->ClearChildren();

	UTextBlock *TextBlock;
	UGridSlot *GridSlot;

	GridWidget->ColumnFill.Add(0.2);
	GridWidget->ColumnFill.Add(0.2);
	GridWidget->ColumnFill.Add(0.2);
	GridWidget->ColumnFill.Add(0.2);
	GridWidget->ColumnFill.Add(0.2);

	// First the header
	TextBlock = NewObject<UTextBlock>();
	TextBlock->SetText(FText::FromString("Name"));
	GridSlot = GridWidget->AddChildToGrid(TextBlock);
	GridSlot->Row = 0;
	GridSlot->Column = 0;

	TextBlock = NewObject<UTextBlock>();
	TextBlock->SetText(FText::FromString("Kills"));
	GridSlot = GridWidget->AddChildToGrid(TextBlock);
	GridSlot->Row = 0;
	GridSlot->Column = 1;

	TextBlock = NewObject<UTextBlock>();
	TextBlock->SetText(FText::FromString("Assists"));
	GridSlot = GridWidget->AddChildToGrid(TextBlock);
	GridSlot->Row = 0;
	GridSlot->Column = 2;

	TextBlock = NewObject<UTextBlock>();
	TextBlock->SetText(FText::FromString("Damage Done"));
	GridSlot = GridWidget->AddChildToGrid(TextBlock);
	GridSlot->Row = 0;
	GridSlot->Column = 3;

	TextBlock = NewObject<UTextBlock>();
	TextBlock->SetText(FText::FromString("Damage Taken"));
	GridSlot = GridWidget->AddChildToGrid(TextBlock);
	GridSlot->Row = 0;
	GridSlot->Column = 4;

	// Now the content
	int row = 1;
	for (auto Player : ConnectedPlayers) {
		TextBlock = NewObject<UTextBlock>();
		TextBlock->SetText(FText::FromString(Player->Name));
		GridSlot = GridWidget->AddChildToGrid(TextBlock);
		GridSlot->Row = row;
		GridSlot->Column = 0;

		TextBlock = NewObject<UTextBlock>();
		TextBlock->SetText(FText::AsNumber(Player->Kills));
		GridSlot = GridWidget->AddChildToGrid(TextBlock);
		GridSlot->Row = row;
		GridSlot->Column = 1;

		TextBlock = NewObject<UTextBlock>();
		TextBlock->SetText(FText::AsNumber(Player->Assists));
		GridSlot = GridWidget->AddChildToGrid(TextBlock);
		GridSlot->Row = row;
		GridSlot->Column = 2;

		TextBlock = NewObject<UTextBlock>();
		TextBlock->SetText(FText::AsNumber(Player->DamageDone));
		GridSlot = GridWidget->AddChildToGrid(TextBlock);
		GridSlot->Row = row;
		GridSlot->Column = 3;

		TextBlock = NewObject<UTextBlock>();
		TextBlock->SetText(FText::AsNumber(Player->DamageTaken));
		GridSlot = GridWidget->AddChildToGrid(TextBlock);
		GridSlot->Row = row;
		GridSlot->Column = 4;

		row++;
	}

	this->SynchronizeProperties();
	this->RebuildWidget();
	this->ForceLayoutPrepass();
	this->InvalidateLayoutAndVolatility();
}