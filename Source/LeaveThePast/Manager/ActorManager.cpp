#include "ActorManager.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "XmlParser/Public/XmlFile.h"
#include "LogManager.h"

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

AActorBase* UActorManager::LoadActorToSceneById(int actorId)
{
	if (GetActorById(actorId) != nullptr)
	{
		return GetActorById(actorId);
	}
	UActorInfoBase* actorInfo = GetActorInfoById(actorId);
	if (actorInfo != nullptr)
	{
		FActorSpawnParameters actorSpawnParameters;
		actorSpawnParameters.bAllowDuringConstructionScript = true;
		actorSpawnParameters.bNoFail = true;
		AActorBase* actor = GWorld->SpawnActor<AActorBase>(actorInfo->GetDefaultPosition(), actorInfo->GetDefaultRotation(), actorSpawnParameters);
		if (actor)
		{
			actor->SetActorInfo(actorInfo);
			actor->Restart();
			actorBaseMap.Add(actor->GetActorId(), actor);
			return actor;
		}
	}
	else
	{
		LogError(FString::Printf(TEXT("配置中不存在演员：%d"), actorId));
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

UActorInfoBase* UActorManager::GetActorInfoById(int actorId)
{
	if (mainActorInfoMap.Contains(actorId))
	{
		return mainActorInfoMap[actorId];
	}
	else if (minorActorInfoMap.Contains(actorId))
	{
		return minorActorInfoMap[actorId];
	}
	else if (massActorInfoMap.Contains(actorId))
	{
		return massActorInfoMap[actorId];
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
