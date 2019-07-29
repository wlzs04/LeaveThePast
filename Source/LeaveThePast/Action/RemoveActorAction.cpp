#include "RemoveActorAction.h"
#include "../Manager/ActorManager.h"
#include "../Manager/LogManager.h"

URemoveActorAction::URemoveActorAction() :UActionBase()
{
	actionName = TEXT("NewActor");
}

void URemoveActorAction::Load(FXmlNode* xmlNode)
{
	for(auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("actorId"))
		{
			actorInfoId = FCString::Atoi(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void URemoveActorAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString URemoveActorAction::ExecuteReal()
{
	UActorManager::GetInstance()->RemoveActorByInfoId(actorInfoId);
	return FString();
}