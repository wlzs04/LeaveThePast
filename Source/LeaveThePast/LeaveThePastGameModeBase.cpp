#include "LeaveThePastGameModeBase.h"
#include "Manager/MainGameManager.h"
#include "Actor/DirectorActor.h"
#include "Engine/World.h"
#include "Engine/Level.h"

void ALeaveThePastGameModeBase::StartPlay()
{
	AGameModeBase::StartPlay();

	gameManager = (UMainGameManager*)(GWorld->GetGameInstance());
	gameManager->InitAll();
	
	directorActor = Cast<ADirectorActor>(GWorld->GetFirstPlayerController()->GetPawn());
	directorActor->SetCanControl(false); 
	
	directorActor->InitCanControlActor();

	if (gameManager->GetSystemData()->GetShowInitUI())
	{
		gameManager->GetUIManager()->ShowInitUI();
	}
	else
	{
		InitFinish();
	}
}

void ALeaveThePastGameModeBase::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	gameManager->Tick(deltaSeconds);
}

void ALeaveThePastGameModeBase::InitFinish()
{
	if (mainGameState == MainGameStateEnum::Init)
	{
		LogNormal(TEXT("游戏初始化结束。"));
		mainGameState = MainGameStateEnum::Normal;
		directorActor->SetCanControl(true);
		StartGame();
	}
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
