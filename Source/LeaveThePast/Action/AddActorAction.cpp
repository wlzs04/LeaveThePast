#include "AddActorAction.h"
#include "../Manager/ActorManager.h"
#include "../Manager/LogManager.h"

UAddActorAction::UAddActorAction() :UActionBase()
{
	actionName = TEXT("AddActor");
}

void UAddActorAction::Load(FXmlNode* xmlNode)
{
	sceneActorInfo.LoadFromXmlNode(xmlNode);

	FString isOnlyString = xmlNode->GetAttribute(TEXT("isOnly"));
	if (!isOnlyString.IsEmpty())
	{
		isOnly = isOnlyString.ToBool();
	}
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
	if (isOnly)
	{
		if(UActorManager::GetInstance()->GetActorByInfoId(sceneActorInfo.actorId)!=nullptr)
		{
			LogWarning(FString::Printf(TEXT("指令AddActor失败，演员InfoId:%d已在场景中。"), sceneActorInfo.actorId));
			return FString();
		}
	}
	UActorInfoBase* actorInfo = UActorManager::GetInstance()->GetNewActorInfoByInfoId(sceneActorInfo.actorId);
	if (actorInfo != nullptr)
	{
		actorInfo->CoverData(sceneActorInfo);
		UActorManager::GetInstance()->LoadActorToSceneByActorInfo(actorInfo);
	}
	return FString();
}