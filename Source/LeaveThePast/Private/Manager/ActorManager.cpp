#include "ActorManager.h"

void UActorManager::LoadAllActor()
{
	LoadMainActor();
	LoadMassActor();
}

void UActorManager::LoadMainActor()
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
		AMainActor* mainActor = NewObject<AMainActor>();
		mainActor->Load(childNode);
		mainActorMap.Add(mainActor->GetActorId(), mainActor);
	}
	xmlFile->Clear();
	delete xmlFile;
	UE_LOG(LogLoad, Log, TEXT("MainActor文件：%s加载完成！"), *mainActorPath);
}

void UActorManager::LoadMassActor()
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
		AMassActor* massActor = NewObject<AMassActor>();
		massActor->Load(childNode);
		massActorMap.Add(massActor->GetActorId(),massActor);
	}
	xmlFile->Clear();
	delete xmlFile;
	UE_LOG(LogLoad, Log, TEXT("MassActor文件：%s加载完成！"), *massActorPath);
}
