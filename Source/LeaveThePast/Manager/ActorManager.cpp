#include "ActorManager.h"
#include "ConfigManager.h"
#include "MainGameManager.h"
#include "LogManager.h"
#include "../Config/Recorder/SceneRecorder.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "XmlParser/Public/XmlFile.h"
#include "Engine/Level.h"
#include "EngineUtils.h"

#include "../Actor/ActorBase.h"
#include "../Actor/MainActorInfo.h"
#include "../Actor/MinorActorInfo.h"
#include "../Actor/MassActorInfo.h"
#include "../Volume/VolumeBase.h"
#include "../Volume/ScriptVolume.h"
#include "../Volume/SceneVolume.h"

UActorManager* UActorManager::actorManager = nullptr;

UActorManager* UActorManager::GetInstance()
{
	return UActorManager::actorManager;
}

void UActorManager::Init()
{
	UActorManager::actorManager = this;
	LoadMainActorInfo();
	LoadMinorActorInfo();
	LoadMassActorInfo();

	LoadAllIegalVolume();
}

void UActorManager::LoadAllActorBySceneId(int sceneId)
{
	USceneRecorder* sceneRecorder = (USceneRecorder*)UConfigManager::GetInstance()->GetConfigByNameId(USceneRecorder::StaticClass(), TEXT("Scene"), sceneId);
	if (sceneRecorder==nullptr)
	{
		LogError(FString::Printf(TEXT("场景：%d不存在。"), sceneId));
		return;
	}
	for (FSceneActorInfo sceneActorInfo : sceneRecorder->GetSceneActorList())
	{
		if (GetActorByInfoId(sceneActorInfo.actorId) == nullptr)
		{
			UActorInfoBase* actorInfo = GetNewActorInfoByInfoId(sceneActorInfo.actorId);
			if (actorInfo != nullptr)
			{
				actorInfo->CoverData(sceneActorInfo);
				LoadActorToSceneByActorInfo(actorInfo);
			}
		}
	}
}

AActorBase* UActorManager::LoadActorToSceneByActorInfo(UActorInfoBase* actorInfo)
{
	if (actorInfo != nullptr)
	{
		FActorSpawnParameters actorSpawnParameters;
		actorSpawnParameters.bAllowDuringConstructionScript = true;
		actorSpawnParameters.bNoFail = true;
		AActorBase* actor = GWorld->SpawnActor<AActorBase>(actorInfo->GetDefaultPosition(), actorInfo->GetDefaultRotation(), actorSpawnParameters);
		if (actor)
		{
			actor->SetActorInfo(actorInfo);
			actor->InitByActorInfo();
			actorBaseByInfoIdMap.Add(actorInfo->GetActorId(), actor);
			return actor;
		}
		else
		{
			LogError(TEXT("LoadActorToSceneByInfoId中AActorBase生成失败。"));
		}
	}
	else
	{
		LogError(TEXT("LoadActorToSceneByInfoId中actorInfo为null。"));
	}
	return nullptr;
}

AActorBase* UActorManager::GetActorByInfoId(int actorInfoId)
{
	if (actorBaseByInfoIdMap.Contains(actorInfoId))
	{
		return actorBaseByInfoIdMap[actorInfoId];
	}
	return nullptr;
}

UActorInfoBase* UActorManager::GetActorInfoByInfoId(int actorInfoId)
{
	if (mainActorInfoMap.Contains(actorInfoId))
	{
		return mainActorInfoMap[actorInfoId];
	}
	else if (minorActorInfoMap.Contains(actorInfoId))
	{
		return minorActorInfoMap[actorInfoId];
	}
	else if (massActorInfoMap.Contains(actorInfoId))
	{
		return massActorInfoMap[actorInfoId];
	}
	else
	{
		LogError(FString::Printf(TEXT("配置中不存在演员：%d"), actorInfoId));
	}
	return nullptr;
}

UActorInfoBase* UActorManager::GetNewActorInfoByInfoId(int actorInfoId)
{
	UActorInfoBase* actorInfo = GetActorInfoByInfoId(actorInfoId);
	if (actorInfo != nullptr)
	{
		UActorInfoBase* newActorInfo = NewObject<UActorInfoBase>();
		newActorInfo->CopyData(actorInfo);
		return newActorInfo;
	}
	return nullptr;
}

int UActorManager::RemoveActorByInfoId(int actorInfoId)
{
	int removeNumber = 0;
	if (actorBaseByInfoIdMap.Contains(actorInfoId))
	{
		actorBaseByInfoIdMap.Remove(actorInfoId);
	}
	return removeNumber;
}

TMap<int, AActorBase*> UActorManager::GetAllActor()
{
	return actorBaseByInfoIdMap;
}

TArray<AVolumeBase*> UActorManager::GetAllVolume()
{
	return volumeList;
}

AVolumeBase* UActorManager::AddVolumeToSceneByVolumeInfo(FString volumeName, FVector position)
{
	if (legalVolumeMap.Contains(volumeName))
	{
		FActorSpawnParameters actorSpawnParameters;
		actorSpawnParameters.bAllowDuringConstructionScript = true;
		actorSpawnParameters.bNoFail = true;

		AVolumeBase* volume = UMainGameManager::GetInstance()->GetGameWorld()->SpawnActor<AScriptVolume>(legalVolumeMap[volumeName]->GetClass(), position, FRotator(0, 0, 0), actorSpawnParameters);
		volumeList.Add(volume);
		return volume;
	}
	else
	{
		LogError(FString::Printf(TEXT("未知体积类型%s，无法生成。"),*volumeName));
	}
	return nullptr;
}

void UActorManager::RemoveVolumeByVolumeValue(FString volumeValue)
{
	for (int i = volumeList.Num() - 1; i >= 0; i--)
	{
		if (volumeList[i]->GetVolumeValue() == volumeValue)
		{
			volumeList[i]->Destroy();
			volumeList.RemoveAt(i);
		}
	}
}

void UActorManager::LoadMainActorInfo()
{
	FString mainActorPath = FPaths::ProjectContentDir() + mainActorRelativePath;

	FXmlFile* xmlFile = new FXmlFile(mainActorPath);
	if (!xmlFile->IsValid())
	{
		LogError(FString::Printf(TEXT("MainActor文件加载失败：%s"), *mainActorPath));
		return;
	}
	FXmlNode* rootNode = xmlFile->GetRootNode();
	for (auto childNode : rootNode->GetChildrenNodes())
	{
		UMainActorInfo* mainActorInfo = NewObject<UMainActorInfo>();
		mainActorInfo->Load(childNode);
		mainActorInfoMap.Add(mainActorInfo->GetActorId(), mainActorInfo);
	}
	xmlFile->Clear();
	delete xmlFile;
	LogNormal(FString::Printf(TEXT("MainActor文件加载完成：%s"), *mainActorPath));
}

void UActorManager::LoadMinorActorInfo()
{
	FString minorActorPath = FPaths::ProjectContentDir() + minorActorRelativePath;

	FXmlFile* xmlFile = new FXmlFile(minorActorPath);
	if (!xmlFile->IsValid())
	{
		LogError(FString::Printf(TEXT("MinorActor文件加载完成：%s"), *minorActorPath));
		return;
	}
	FXmlNode* rootNode = xmlFile->GetRootNode();
	for (auto childNode : rootNode->GetChildrenNodes())
	{
		UMinorActorInfo* minorActorInfo = NewObject<UMinorActorInfo>();
		minorActorInfo->Load(childNode);
		minorActorInfoMap.Add(minorActorInfo->GetActorId(), minorActorInfo);
	}
	xmlFile->Clear();
	delete xmlFile;
	LogNormal(FString::Printf(TEXT("MinorActor文件加载完成：%s"), *minorActorPath));
}

void UActorManager::LoadMassActorInfo()
{
	FString massActorPath = FPaths::ProjectContentDir() + massActorRelativePath;

	FXmlFile* xmlFile = new FXmlFile(massActorPath);
	if (!xmlFile->IsValid())
	{
		LogError(FString::Printf(TEXT("MassActor文件加载完成：%s"), *massActorPath));
		return;
	}
	FXmlNode* rootNode = xmlFile->GetRootNode();
	for (auto childNode : rootNode->GetChildrenNodes())
	{
		UMassActorInfo* massActorInfo = NewObject<UMassActorInfo>();
		massActorInfo->Load(childNode);
		massActorInfoMap.Add(massActorInfo->GetActorId(), massActorInfo);
	}
	xmlFile->Clear();
	delete xmlFile;
	LogNormal(FString::Printf(TEXT("MassActor文件加载完成：%s"), *massActorPath));
}

void UActorManager::LoadAllIegalVolume()
{
	AddIegalVolume(NewObject<AScriptVolume>(this));
	AddIegalVolume(NewObject<ASceneVolume>(this));
}

void UActorManager::AddIegalVolume(AVolumeBase* volumeBase)
{
	legalVolumeMap.Add(volumeBase->GetVolumeName(), volumeBase);
}
