#include "LeaveThePastGameModeBase.h"
#include "Manager/MainGameManager.h"
#include "Actor/DirectorActor.h"
//#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/Level.h"

void ALeaveThePastGameModeBase::StartPlay()
{
	AGameModeBase::StartPlay();

	gameManager = (UMainGameManager*)(GWorld->GetGameInstance());
	gameManager->InitAll();

	directorActor = Cast<ADirectorActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
	directorActor->InitActorList();

	LogNormal(TEXT("游戏初始化结束。"));

	if (gameManager->GetSystemData()->GetShowInitUI())
	{
		gameManager->GetUIManager()->LoadUIByName(TEXT("InitUI"))->AddToViewport();
	}
	else
	{
		StartGame();
	}
}

void ALeaveThePastGameModeBase::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	gameManager->Tick(deltaSeconds);
}

void ALeaveThePastGameModeBase::StartGame()
{
	gameManager->GetUIManager()->ShowMainUI();

	gameManager->StartTime();
}

void ALeaveThePastGameModeBase::PauseGame()
{
	gameManager->GetUIManager()->ShowPauseUI();
	gameManager->StopTime();
}

void ALeaveThePastGameModeBase::ContinueGame()
{
	gameManager->GetUIManager()->HidePauseUI();
	gameManager->StartTime();
}

void ALeaveThePastGameModeBase::EndGame()
{
	gameManager->ExitGame();
}

UMainGameManager* ALeaveThePastGameModeBase::GetGameManager()
{
	return gameManager;
}
