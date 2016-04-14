// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "ScoreOverlay.h"
#include "TextBlockEx.h"

void UScoreOverlay::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	auto GameState = GetWorld()->GetGameState<AMainGameState>();

	if (GameState) {
		if (GameState->ConnectedPlayersArray != ConnectedPlayers) {
			ConnectedPlayers = GameState->ConnectedPlayersArray;

			this->UpdateScoreTable();
		}
	}

	for (int i = 0; i < ConnectedPlayers.Num(); i++) {
		auto Player = ConnectedPlayers[i];
		
		NameWidgets[i]->SetText(FText::FromString(Player->Name));
		KillsWidgets[i]->SetText(FText::AsNumber(Player->Kills));
		AssistsWidgets[i]->SetText(FText::AsNumber(Player->Assists));
		DamageDoneWidgets[i]->SetText(FText::AsNumber(Player->DamageDone));
		DamageTakenWidgets[i]->SetText(FText::AsNumber(Player->DamageTaken));
	}
}

void UScoreOverlay::UpdateScoreTable()
{
	GridWidget->ClearChildren();

	auto createTextBlock = [this](int row, int column, const FText& text) -> UTextBlockEx* {
		UTextBlockEx* TextBlock = NewObject<UTextBlockEx>();
		TextBlock->SetText(text);
		TextBlock->SetMargin(50, 0, 50, 0);
		UGridSlot* GridSlot = GridWidget->AddChildToGrid(TextBlock);
		GridSlot->SetRow(row);
		GridSlot->SetColumn(column);
		GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);

		return TextBlock;
	};

	// First the header
	
	createTextBlock(0, 0, FText::FromString("Name"));
	createTextBlock(0, 1, FText::FromString("Kills"));
	createTextBlock(0, 2, FText::FromString("Assists"));
	createTextBlock(0, 3, FText::FromString("Damage Done"));
	createTextBlock(0, 4, FText::FromString("Damage Taken"));

	// Now the content
	int row = 1;
	FText emptyString;

	for (auto Player : ConnectedPlayers) {
		NameWidgets.Add(createTextBlock(row, 0, emptyString));
		KillsWidgets.Add(createTextBlock(row, 1, emptyString));
		AssistsWidgets.Add(createTextBlock(row, 2, emptyString));
		DamageDoneWidgets.Add(createTextBlock(row, 3, emptyString));
		DamageTakenWidgets.Add(createTextBlock(row, 4, emptyString));

		row++;
	}
}