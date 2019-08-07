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
#include "Runtime/Core/Public/HAL/FileManager.h"

#include "../Actor/ActorBase.h"
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
	LoadActorInfo();

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
	for (int actorId : sceneRecorder->GetSceneActorIdList())
	{
		if (GetActorByInfoId(actorId) == nullptr)
		{
			UActorInfoBase* actorInfo = GetNewActorInfoByInfoId(actorId);
			if (actorInfo != nullptr)
			{
				LoadActorToSceneByActorInfo(actorInfo);
			}
			else
			{
				LogError(FString::Printf(TEXT("场景:%d中的actorId:%d在演员配置表中不存在。"), sceneId, actorId));
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
	if (actorInfoMap.Contains(actorInfoId))
	{
		return actorInfoMap[actorInfoId];
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
	else
	{
		LogError(FString::Printf(TEXT("配置中不存在演员：%d"), actorInfoId));
	}
	return nullptr;
}

void UActorManager::RemoveActorByInfoId(int actorInfoId)
{
	if (actorBaseByInfoIdMap.Contains(actorInfoId))
	{
		actorBaseByInfoIdMap[actorInfoId]->Destroy();
		actorBaseByInfoIdMap.Remove(actorInfoId);
	}
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

void UActorManager::LoadActorInfo()
{
	FString actorInfoPath = FPaths::ProjectContentDir() + actorInfoRootPath;
	//使用此方法查找文件时需要添加文件类型
	FString actorInfoRootFilePath = actorInfoPath + TEXT("*.*");
	TArray<FString> actorInfoFilePaths;
	IFileManager::Get().FindFiles(actorInfoFilePaths, *actorInfoRootFilePath, true, false);

	UEnum* actorEnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ActorEnum"), true);

	for (auto var : actorInfoFilePaths)
	{
		FString actorInfoRealPath = actorInfoPath + var;
		LogNormal(FString::Printf(TEXT("Actor文件开始加载：%s"), *actorInfoRealPath));
		FXmlFile* xmlFile = new FXmlFile(actorInfoRealPath);
		if (!xmlFile->IsValid())
		{
			LogError(FString::Printf(TEXT("Actor文件加载失败：%s"), *actorInfoRealPath));
			return;
		}

		FXmlNode* rootNode = xmlFile->GetRootNode();
		ActorEnum actorEnum = ActorEnum::Unknown;
		FString actorEnumString = rootNode->GetAttribute(TEXT("actorEnum"));
		actorEnum = (ActorEnum)actorEnumPtr->GetValueByNameString(actorEnumString);
		for (auto childNode : rootNode->GetChildrenNodes())
		{
			FString childNodeName = childNode->GetTag();
			if (childNodeName == TEXT("Actor"))
			{
				UActorInfoBase* actorInfo = NewObject<UActorInfoBase>();
				actorInfo->SetActorEnum(actorEnum);
				actorInfo->Load(childNode);
				actorInfoMap.Add(actorInfo->GetActorId(), actorInfo);
			}
			else
			{
				LogWarning(FString::Printf(TEXT("Actor文件:%s中存在未知节点：%s"), *actorInfoRealPath,*childNodeName));
			}
		}

		xmlFile->Clear();
		delete xmlFile;
		LogNormal(FString::Printf(TEXT("Actor文件加载完成：%s"), *actorInfoRealPath));
	}
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
