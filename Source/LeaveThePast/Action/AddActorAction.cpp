#include "AddActorAction.h"
#include "../Manager/ActorManager.h"

UAddActorAction::UAddActorAction() :UActionBase()
{
	actionName = TEXT("AddActor");
}

void UAddActorAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);

	sceneActorInfo.LoadFromXmlNode(xmlNode);
}

void UAddActorAction::Update()
{
	if (isCompleted == false)
	{
		isCompleted = true;
	}
}

FString UAddActorAction::ExecuteReal()
{
	isCompleted = false;
	UActorInfoBase* actorInfo = UActorManager::GetInstance()->GetNewActorInfoByInfoId(sceneActorInfo.actorId);
	if (actorInfo != nullptr)
	{
		actorInfo->CoverData(sceneActorInfo);
		UActorManager::GetInstance()->LoadActorToSceneByActorInfo(actorInfo);
	}
	return FString();
}