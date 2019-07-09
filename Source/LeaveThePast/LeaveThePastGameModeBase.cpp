#include "LeaveThePastGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

void ALeaveThePastGameModeBase::StartPlay()
{
	AGameModeBase::StartPlay();
	gameManager = (UMainGameManager*)(GWorld->GetGameInstance());
	gameManager->InitAll();
	gameManager->StartTime();

	if (gameManager->GetSystemData()->GetShowInitUI())
	{
		gameManager->GetUIManager()->LoadUIByName(TEXT("InitUI"))->AddToViewport();
	}

	ADirectorActor* directorActor = Cast<ADirectorActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
	directorActor->InitActorList();

	gameManager->GetUIManager()->ShowMainUI();
	USoundBase* sound = gameManager->GetAudioManager()->GetAudioById(10001);
}

void ALeaveThePastGameModeBase::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	gameManager->Tick(deltaSeconds);
}

UMainGameManager* ALeaveThePastGameModeBase::GetGameManager()
{
	return gameManager;
}
