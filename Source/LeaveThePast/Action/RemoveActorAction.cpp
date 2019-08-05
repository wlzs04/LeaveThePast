#include "RemoveActorAction.h"
#include "../Manager/ActorManager.h"
#include "../Manager/LogManager.h"

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

void URemoveActorAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			actorInfoId = FCString::Atoi(*attributeValue);
			break;
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
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