#include "ActorManager.h"
#include "Engine/World.h"

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
			AActorBase* actor = GWorld->SpawnActor<AActorBase>(actor->GetDefaultPosition(), actor->GetDefaultRotation());
			actor->SetActorInfo(actorInfo);
			actorBaseMap.Add(actor->GetActorId(),actor);
		}
	}
}

AActorBase* UActorManager::GetActorById(int actorId)
{
	if (actorBaseMap.Contains(actorId))
	{
		return actorBaseMap[actorId];
	}
	/*if (mainActorMap.Contains(actorId))
	{
		return mainActorMap[actorId];
	}
	else if (minorActorMap.Contains(actorId))
	{
		return minorActorMap[actorId];
	}
	else if (massActorMap.Contains(actorId))
	{
		return massActorMap[actorId];
	}*/
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
