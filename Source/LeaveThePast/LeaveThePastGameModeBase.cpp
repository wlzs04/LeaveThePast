#include "LeaveThePastGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/Level.h"

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
	LogNormal(TEXT("初始化场景中已存在的演员信息"));
	//初始化场景中已存在的演员信息
	TActorIterator<AActorBase> actorItr = TActorIterator<AActorBase>(GetWorld(), AActorBase::StaticClass());
	//for (int i = 0; i < GetLevel()->Actors.Num(); i++)
	for (actorItr; actorItr; ++actorItr)
	{
		AActorBase* actorBase = *actorItr;
		if (actorBase != nullptr && actorBase->actorIdForEditor!=0)
		{
			actorBase->SetActorInfo(gameManager->GetActorManager()->GetActorInfoById(actorBase->actorIdForEditor));
		}
	}

	ADirectorActor* directorActor = Cast<ADirectorActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
	directorActor->InitActorList();

	gameManager->GetUIManager()->ShowMainUI();
	USoundCue* sound = gameManager->GetAudioManager()->GetAudioById(10001);
	//directorActor->GetCameraActor()->StartPlayVoiceSound(sound);
	directorActor->StartPlayBGMSound(sound);

	USystemData* systemData = gameManager->GetSystemData();
	gameManager->GetAudioManager()->SetMainSoundVolume(systemData->GetMainSoundVolume());
	gameManager->GetAudioManager()->SetBGMSoundVolume(systemData->GetBGMSoundVolume());
	gameManager->GetAudioManager()->SetVoiceSoundVolume(systemData->GetVoiceSoundVolume());
	gameManager->GetAudioManager()->SetEffectSoundVolume(systemData->GetEffectSoundVolume());
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
