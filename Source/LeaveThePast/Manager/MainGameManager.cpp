#include "MainGameManager.h"
#include "Kismet/KismetSystemLibrary.h"

#include "FileHelper.h"
#include "LogMacros.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#include "../Actor/DirectorActor.h"

UMainGameManager* UMainGameManager::gameManager = nullptr;

UMainGameManager* UMainGameManager::GetInstance()
{
	return UMainGameManager::gameManager;
}

void UMainGameManager::InitAll()
{
	if (!haveInited)
	{
		UMainGameManager::gameManager = this;
		InitManager();

		systemData = NewObject<USystemData>(this);
		ReloadSystemData();

		userData = NewObject<UUserData>(this);
		ReloadUserData();

		debugData = NewObject<UDebugData>(this);
		ReloadDebugData();

		gameWorld = GetWorld();

		directorActor = Cast<ADirectorActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
		
		haveInited = true;
	}
}

void UMainGameManager::ReloadSystemData()
{
	systemData->Load();
	GetAudioManager()->SetMainSoundVolume(systemData->GetMainSoundVolume());
	GetAudioManager()->SetBGMSoundVolume(systemData->GetBGMSoundVolume());
	GetAudioManager()->SetVoiceSoundVolume(systemData->GetVoiceSoundVolume());
	GetAudioManager()->SetEffectSoundVolume(systemData->GetEffectSoundVolume());
}

void UMainGameManager::ReloadUserData()
{
	userData->Load();
}

void UMainGameManager::ReloadDebugData()
{
	debugData->Load();
}

void UMainGameManager::UseItem(int itemId)
{
	if (userData->GetItemNumberById(itemId)>0)
	{
		if (itemId == 20001)
		{
			GetUIManager()->AddMessageTipById(10007);
		}
	}
	userData->ReduceItem(itemId,1);
}

void UMainGameManager::EnterScene(int sceneId)
{
	USceneRecorder* sceneRecorder = (USceneRecorder*)UConfigManager::GetInstance()->GetConfigByNameId(USceneRecorder::StaticClass(), TEXT("Scene"), sceneId);
	if (sceneRecorder != nullptr)
	{
		userData->SetSceneId(sceneId);
		directorActor->StartPlayBGMSound(GetAudioManager()->GetAudioById(sceneRecorder->GetBGMId()));
		//GetActorManager()->LoadAllActorBySceneId(sceneId);
	}
}

UWorld* UMainGameManager::GetGameWorld()
{
	return gameWorld;
}

void UMainGameManager::InitManager()
{
	logManager = NewObject<ULogManager>(this);
	logManager->Init();

	configManager = NewObject<UConfigManager>(this);
	configManager->Init();

	audioManager = NewObject<UAudioManager>(this);
	audioManager->Init();

	scriptManager = NewObject<UScriptManager>(this);
	scriptManager->Init();

	actorManager = NewObject<UActorManager>(this); 
	actorManager->Init();

	uiManager = NewObject<UUIManager>(this);
	uiManager->Init();
}

void UMainGameManager::StartTime()
{
	startTime = true;
}

void UMainGameManager::StopTime()
{
	startTime = false;
}

bool UMainGameManager::IsStartTime()
{
	return startTime;
}

FTimeData UMainGameManager::GetRealTimeData()
{
	return realTimeData;
}

FTimeData UMainGameManager::GetGameTimeData()
{
	return userData->GetGameTimeData();
}

void UMainGameManager::Tick(float secondTime)
{
	if (startTime)
	{
		realTimeData.Tick(secondTime);
		userData->Tick(secondTime);
		scriptManager->Tick();
	}
}

void UMainGameManager::SaveSystemData()
{
	systemData->Save();
}

USystemData* UMainGameManager::GetSystemData()
{
	return systemData;
}

void UMainGameManager::SaveUserData()
{
	userData->Save();
}

UUserData* UMainGameManager::GetUserData()
{
	return userData;
}

void UMainGameManager::SaveDebugData()
{
	debugData->Save();
}

UDebugData* UMainGameManager::GetDebugData()
{
	return debugData;
}

void UMainGameManager::ExitGame()
{
	SaveSystemData();
	SaveDebugData();
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

UConfigManager* UMainGameManager::GetConfigManager()
{
	return configManager;
}

UScriptManager* UMainGameManager::GetScriptManager()
{
	return scriptManager;
}

UActorManager* UMainGameManager::GetActorManager()
{
	return actorManager;
}

ULogManager* UMainGameManager::GetLogManager()
{
	return logManager;
}

UUIManager* UMainGameManager::GetUIManager()
{
	return uiManager;
}

UAudioManager* UMainGameManager::GetAudioManager()
{
	return audioManager;
}

FString UMainGameManager::GetArtresPath()
{
	return FPaths::ProjectContentDir() + TEXT("GameContent/Artres/");
}