#include "ActorManager.h"
#include "Engine/World.h"
#include "Public/UObject/ConstructorHelpers.h"

UActorManager::UActorManager():Super()
{
	static ConstructorHelpers::FClassFinder<AActor> BP_MyActor(TEXT("Blueprint'/Game/GameContent/WorldObject/Actor/ActorBase_BP.ActorBase_BP_C'"));
	if (BP_MyActor.Succeeded())
	{
		BPMyActorClass = BP_MyActor.Class;
	}
}

void UActorManager::LoadAllActorInfo()
{
	LoadMainActorInfo();
	LoadMinorActorInfo();
	LoadMassActorInfo();
}

void UActorManager::LoadAllPermanentActorToScene()
{
	UClass* actorBlueprintClass = StaticLoadClass(UObject::StaticClass(), NULL, TEXT("/Game/GameContent/WorldObject/Actor/MassActor_BP.MassActor_BP"), NULL, LOAD_None, NULL);
	
	for (auto pair: massActorInfoMap)
	{
		UMassActorInfo* actorInfo = pair.Value;
		if (actorInfo->IsPermanent())
		{
			AActorBase* actor = GWorld->SpawnActor<AActorBase>(actorInfo->GetDefaultPosition(), actorInfo->GetDefaultRotation());
			actor->SetActorInfo(actorInfo);
			actorBaseMap.Add(actor->GetActorId(),actor);
		}
	}
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
		AActorBase* actor = GWorld->SpawnActor<AActorBase>(BPMyActorClass,actorInfo->GetDefaultPosition(), actorInfo->GetDefaultRotation());
		actor->SetActorInfo(actorInfo);
		actorBaseMap.Add(actor->GetActorId(), actor);
		return actor;
	}
	else
	{
		UE_LOG(LogLoad, Error, TEXT("配置中不存在演员：%d"), actorId);
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
		UE_LOG(LogLoad, Error, TEXT("MainActor文件加载失败：%s"), *mainActorPath);
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
	UE_LOG(LogLoad, Log, TEXT("MainActor文件：%s加载完成！"), *mainActorPath);
}

void UActorManager::LoadMinorActorInfo()
{
	FString minorActorPath = FPaths::ProjectContentDir() + minorActorRelativePath;

	FXmlFile* xmlFile = new FXmlFile(minorActorPath);
	if (!xmlFile->IsValid())
	{
		UE_LOG(LogLoad, Error, TEXT("MinorActor文件加载失败：%s"), *minorActorPath);
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
	UE_LOG(LogLoad, Log, TEXT("MinorActor文件：%s加载完成！"), *minorActorPath);
}

void UActorManager::LoadMassActorInfo()
{
	FString massActorPath = FPaths::ProjectContentDir() + massActorRelativePath;

	FXmlFile* xmlFile = new FXmlFile(massActorPath);
	if (!xmlFile->IsValid())
	{
		UE_LOG(LogLoad, Error, TEXT("MassActor文件加载失败：%s"), *massActorPath);
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
	UE_LOG(LogLoad, Log, TEXT("MassActor文件：%s加载完成！"), *massActorPath);
}
