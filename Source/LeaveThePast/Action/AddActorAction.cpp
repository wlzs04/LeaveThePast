#include "AddActorAction.h"
#include "../Manager/ActorManager.h"
#include "../Actor/ActorInfoBase.h"
#include "../Manager/LogManager.h"

UAddActorAction::UAddActorAction() :UActionBase()
{
	actionName = TEXT("AddActor");
}

void UAddActorAction::Load(FXmlNode* xmlNode)
{
	sceneActorInfo.LoadFromXmlNode(xmlNode);
}

void UAddActorAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UAddActorAction::ExecuteReal()
{
	if (UActorManager::GetInstance()->GetActorByInfoId(sceneActorInfo.actorId) == nullptr)
	{
		UActorInfoBase* actorInfo = UActorManager::GetInstance()->GetNewActorInfoByInfoId(sceneActorInfo.actorId);
		if (actorInfo != nullptr)
		{
			actorInfo->CoverData(sceneActorInfo);
			UActorManager::GetInstance()->LoadActorToSceneByActorInfo(actorInfo);
		}
	}
	return FString();
}