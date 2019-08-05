#include "ChangeControlActorAction.h"
#include "../Manager/ActorManager.h"
#include "../Manager/LogManager.h"
#include "../Actor/DirectorActor.h"
#include "../Actor/ActorBase.h"

void UChangeControlActorAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
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

void UChangeControlActorAction::Load(TArray<FString> paramList)
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

void UChangeControlActorAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UChangeControlActorAction::ExecuteReal()
{
	AActorBase* executeActor = UActorManager::GetInstance()->GetActorByInfoId(actorInfoId);
	if (executeActor != nullptr)
	{
		ADirectorActor::GetInstance()->SetControlActorById(executeActor->GetActorInfo()->GetActorId());
	}
	else
	{
		LogError(FString::Printf(TEXT("指令：ChangeCameraActor没有找到演员InfoId：%d"), actorInfoId));
	}
	return FString();
}