// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "GameOverHUD.h"
#include "Components/TextBlock.h"
#include "Widgets/SCompoundWidget.h"
#include "Components/Button.h"
#include "MainGameState.h"

void UGameOverHUD::OnPlayerReady(AMyPlayerState* player)
{
	if (State == UGameOverState::Ready) {
		auto players = Cast<AMainGameState>(GetWorld()->GetGameState())->GetConnectedPlayers();
	}
}

void UGameOverHUD::NativeConstruct()
{
	Super::NativeConstruct();

	RestartButtonWidget->OnClicked.AddDynamic(this, &UGameOverHUD::OnRestartClicked);
}

void UGameOverHUD::OnRestartClicked()
{
	SetState(Ready);

	OnRestartClick.Broadcast();
}

void UGameOverHUD::UpdateState()
{
	auto player = GetWorld()->GetFirstPlayerController();
	if (player) {
		auto PlayerState = Cast<AMyPlayerState>(player->PlayerState);
		if (PlayerState && PlayerState->Initialized) {
			if (State == PlayerAlive) {
				if (!PlayerState->IsAlive()) {
					SetState(PlayerDead);
				}
			}
			else {
				if (PlayerState->IsAlive()) {
					SetState(PlayerAlive);
				}
				else {
					switch (State) {
					case PlayerDead:
					{
						auto connectedPlayers = Cast<AMainGameState>(GetWorld()->GetGameState())->GetConnectedPlayers();
						bool allDead = true;
						for (auto player : connectedPlayers) {
							allDead &= !player.Value->IsAlive();
						}
						if (allDead) {
							SetState(ReadyCheck);
						}
						break;
					}

					case ReadyCheck:
						break;

					case Ready:
						break;
					}
				}
			}
		}
	}
}

void UGameOverHUD::SetState(UGameOverState newState)
{
	State = newState;

	switch (State) {
	case PlayerAlive:
		this->SetVisibility(ESlateVisibility::Hidden);
		break;

	case PlayerDead:
		this->SetVisibility(ESlateVisibility::Visible);
		this->RestartButtonWidget->SetVisibility(ESlateVisibility::Hidden);
		this->GameOverTextWidget->SetText(FText::FromString(FString("You Are Dead")));
		break;

	case ReadyCheck:
		this->SetVisibility(ESlateVisibility::Visible);
		this->RestartButtonWidget->SetVisibility(ESlateVisibility::Visible);
		this->GameOverTextWidget->SetText(FText::FromString(FString("Game Over")));
		break;

	case Ready:
		this->SetVisibility(ESlateVisibility::Visible);
		this->RestartButtonWidget->SetVisibility(ESlateVisibility::Hidden);
		this->GameOverTextWidget->SetText(FText::FromString(FString("Waiting for teammates")));
		break;
	}
}
