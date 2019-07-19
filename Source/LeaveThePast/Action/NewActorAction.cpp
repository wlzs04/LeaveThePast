#include "NewActorAction.h"
#include "../Manager/ActorManager.h"

UNewActorAction::UNewActorAction() :UActionBase()
{
	actionName = TEXT("NewActor");
}

void UNewActorAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);

	sceneActorInfo.LoadFromXmlNode(xmlNode);
}

void UNewActorAction::Update()
{
	if (isCompleted == false)
	{
		isCompleted = true;
	}
}

void UNewActorAction::ExecuteReal()
{
	isCompleted = false;
	UActorInfoBase* actorInfo = UActorManager::GetInstance()->GetNewActorInfoByInfoId(sceneActorInfo.actorId);
	if (actorInfo != nullptr)
	{
		actorInfo->CoverData(sceneActorInfo);
		UActorManager::GetInstance()->LoadActorToSceneByActorInfo(actorInfo);
	}
}
