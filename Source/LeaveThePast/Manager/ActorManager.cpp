#include "ActorManager.h"
#include "ConfigManager.h"
#include "LogManager.h"
#include "../Config/Recorder/SceneRecorder.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "XmlParser/Public/XmlFile.h"
#include "Engine/Level.h"
#include "EngineUtils.h"

UActorManager* UActorManager::actorManager = nullptr;

UActorManager* UActorManager::GetInstance()
{
	return UActorManager::actorManager;
}

void UActorManager::Init()
{
	UActorManager::actorManager = this;
	LoadAllActorInfo();
}

void UActorManager::LoadAllActorInfo()
{
	LoadMainActorInfo();
	LoadMinorActorInfo();
	LoadMassActorInfo();
}

//void UActorManager::LoadAllActorFromScene()
//{
//	LogNormal(TEXT("初始化场景中已存在的演员信息"));
//	TActorIterator<AActorBase> actorItr = TActorIterator<AActorBase>(GetWorld(), AActorBase::StaticClass());
//	for (actorItr; actorItr; ++actorItr)
//	{
//		AActorBase* actorBase = *actorItr;
//		if (actorBase != nullptr && actorBase->actorIdForEditor != 0)
//		{
//			actorBase->SetActorInfo(GetActorInfoById(actorBase->actorIdForEditor));
//		}
//	}
//}

void UActorManager::LoadAllActorBySceneId(int sceneId)
{
	USceneRecorder* sceneRecorder = (USceneRecorder*)UConfigManager::GetInstance()->GetConfigByNameId(USceneRecorder::StaticClass(), TEXT("Scene"), sceneId);
	for (FSceneActorInfo sceneActorInfo : sceneRecorder->GetSceneActorList())
	{
		UActorInfoBase* actorInfo = GetNewActorInfoByInfoId(sceneActorInfo.actorId);
		actorInfo->CoverData(sceneActorInfo);
		AActorBase* actorBase = LoadActorToSceneByActorInfo(actorInfo);
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
			actorIdUnique++;
			actor->SetActorId(actorIdUnique);
			actorBaseMap.Add(actorIdUnique, actor);
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

AActorBase* UActorManager::GetActorById(int actorId)
{
	if (actorBaseMap.Contains(actorId))
	{
		return actorBaseMap[actorId];
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
