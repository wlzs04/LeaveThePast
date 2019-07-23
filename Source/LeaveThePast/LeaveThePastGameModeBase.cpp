#include "LeaveThePastGameModeBase.h"
#include "Manager/MainGameManager.h"
#include "Actor/DirectorActor.h"
#include "Engine/World.h"
#include "Engine/Level.h"

ALeaveThePastGameModeBase* ALeaveThePastGameModeBase::leaveThePastGameModeBase = nullptr;

ALeaveThePastGameModeBase* ALeaveThePastGameModeBase::GetInstance()
{
	return leaveThePastGameModeBase;
}

void ALeaveThePastGameModeBase::StartPlay()
{
	AGameModeBase::StartPlay();

	ALeaveThePastGameModeBase::leaveThePastGameModeBase = this;

	gameManager = (UMainGameManager*)(GWorld->GetGameInstance());
	gameManager->InitAll();

	InitDebugCommand();

	scriptVolumeBPClass = LoadClass<AActor>(NULL, TEXT("Actor'/Game/GameContent/WorldObject/Volume/ScriptVolumeBP.ScriptVolumeBP_C'"));

	UClass* skyObj = LoadClass<AActor>(NULL, TEXT("Actor'/Game/GameContent/WorldObject/Sky/SkySphereBP.SkySphereBP_C'"));

	TActorIterator<AActor> actorItr = TActorIterator<AActor>(GetWorld(), skyObj);
	for (actorItr; actorItr; ++actorItr)
	{
		if (skyBPActor == nullptr)
		{
			skyBPActor = *actorItr;
		}
		else
		{
			LogError(TEXT("场景中存在多个天空球！"));
		}
	}

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

AActor* ALeaveThePastGameModeBase::GetSkyBPActor()
{
	return skyBPActor;
}

void ALeaveThePastGameModeBase::RefreshSky()
{
	UFunction* functionSetInfo = skyBPActor->FindFunction(TEXT("RefreshSkyByGameTime"));
	bool focus = false;
	if (functionSetInfo)
	{
		skyBPActor->ProcessEvent(functionSetInfo, nullptr);
	}
}

UClass* ALeaveThePastGameModeBase::GetScriptVolumeBPClass()
{
	return scriptVolumeBPClass;
}
