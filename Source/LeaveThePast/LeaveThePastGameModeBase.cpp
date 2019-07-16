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

	if (gameManager->GetSystemData()->GetShowInitUI())
	{
		gameManager->GetUIManager()->LoadUIByName(TEXT("InitUI"))->AddToViewport();
	}

	LogNormal(TEXT("初始化场景中已存在的演员信息"));
	//初始化场景中已存在的演员信息
	TActorIterator<AActorBase> actorItr = TActorIterator<AActorBase>(GetWorld(), AActorBase::StaticClass());
	for (actorItr; actorItr; ++actorItr)
	{
		AActorBase* actorBase = *actorItr;
		if (actorBase != nullptr && actorBase->actorIdForEditor!=0)
		{
			actorBase->SetActorInfo(gameManager->GetActorManager()->GetActorInfoById(actorBase->actorIdForEditor));
		}
	}

	directorActor = Cast<ADirectorActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
	directorActor->InitActorList();

	gameManager->GetUIManager()->ShowMainUI();
	//USoundCue* sound = gameManager->GetAudioManager()->GetAudioById(10001);
	//directorActor->GetCameraActor()->StartPlayVoiceSound(sound);
	//directorActor->StartPlayBGMSound(sound);

	LogNormal(TEXT("游戏初始化结束。"));
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
