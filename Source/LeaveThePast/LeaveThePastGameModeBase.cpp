#include "LeaveThePastGameModeBase.h"
#include "Manager/MainGameManager.h"
#include "Manager/LogManager.h"
#include "Manager/UIManager.h"
#include "Manager/ScriptManager.h"
#include "Config/SystemData.h"
#include "Config/UserData.h"
#include "Actor/DirectorActor.h"
#include "Engine/World.h"
#include "Engine/Level.h"
#include "Engine/Public/EngineUtils.h"

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
	
	directorActor->InitActor();

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

	if (mainGameState == MainGameStateEnum::Normal)
	{
		gameManager->Tick(deltaSeconds);
		
		skyBPActor->SetActorRelativeLocation(directorActor->GetActorLocation()+FVector(0,0,500));

		//RefreshSky();
	}
}

void ALeaveThePastGameModeBase::InitFinish()
{
	if (mainGameState == MainGameStateEnum::Init)
	{
		LogNormal(TEXT("游戏初始化结束。"));
		mainGameState = MainGameStateEnum::Normal;
		directorActor->SetCanControl(true);
		StartGame();

		UFunction* functionSetCloudy = skyBPActor->FindFunction(TEXT("RefreshCloudy"));
		if (functionSetCloudy)
		{
			float cloudyValue = gameManager->GetUserData()->GetCloudyValue();
			skyBPActor->ProcessEvent(functionSetCloudy, &cloudyValue);
		}
		else
		{
			LogError(TEXT("天空体没有方法RefreshCloudy。"));
		}
		UFunction* functionSetRain = skyBPActor->FindFunction(TEXT("RefreshRain"));
		if (functionSetRain)
		{
			int rainValue = gameManager->GetUserData()->GetRainValue();
			skyBPActor->ProcessEvent(functionSetRain, &rainValue);
		}
		else
		{
			LogError(TEXT("天空体没有方法RefreshRain。"));
		}
	}
}

void ALeaveThePastGameModeBase::StartGame()
{
	gameManager->GetUIManager()->ShowMainUI();
	gameManager->StartTime();

	//判断是否有需要在游戏开始后运行的脚本
	gameManager->GetScriptManager()->StartNextScript();
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

//void ALeaveThePastGameModeBase::RefreshSky(bool focus)
//{
//	UFunction* functionSetInfo = skyBPActor->FindFunction(TEXT("RefreshSkyByGameTime"));
//	if (functionSetInfo)
//	{
//		skyBPActor->ProcessEvent(functionSetInfo, &focus);
//	}
//}