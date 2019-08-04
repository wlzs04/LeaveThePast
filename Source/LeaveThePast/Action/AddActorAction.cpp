#include "AddActorAction.h"
#include "../Manager/ActorManager.h"
#include "../Actor/ActorInfoBase.h"
#include "../Actor/ActorBase.h"
#include "../Manager/LogManager.h"
#include "../Manager/HelpManager.h"

void UAddActorAction::Load(FXmlNode* xmlNode)
{
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		
		if (attributeName == TEXT("actorId"))
		{
			actorId = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("position"))
		{
			position = UHelpManager::ConvertFStringToFVector(attributeValue);
			needReplacePosition = true;
		}
		else if (attributeName == TEXT("rotation"))
		{
			rotation = UHelpManager::ConvertFStringToFRotator(attributeValue);
			needReplaceRotation = true;
		}
		else
		{
			LogWarning(FString::Printf(TEXT("指令:%s配置中存在未知属性:%s！"), *actionName, *attributeName));
		}
	}
}

void UAddActorAction::Load(TArray<FString> paramList)
{
	if (paramList.Num() > 1)
	{
		actorId = FCString::Atoi(*paramList[1]);
	}
	if (paramList.Num() > 2)
	{
		position = UHelpManager::ConvertFStringToFVector(paramList[2]);
		needReplacePosition = true;
	}
	if (paramList.Num() > 3)
	{
		rotation = UHelpManager::ConvertFStringToFRotator(paramList[3]);
		needReplaceRotation = true;
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
	if (UActorManager::GetInstance()->GetActorByInfoId(actorId) == nullptr)
	{
		UActorInfoBase* actorInfo = UActorManager::GetInstance()->GetNewActorInfoByInfoId(actorId);
		if (actorInfo != nullptr)
		{
			AActorBase* actor = UActorManager::GetInstance()->LoadActorToSceneByActorInfo(actorInfo);
			if (needReplacePosition)
			{
				actor->SetActorLocation(position);
			}
			if(needReplaceRotation)
			{
				actor->SetActorRotation(rotation);
			}
		}
		else
		{
			LogError(FString::Printf(TEXT("指令：%s配置中没有演员id：%d。"), *actionName, actorId));
		}
	}
	else
	{
		LogError(FString::Printf(TEXT("指令：%s场景中已存在指定演员%d。"),*actionName ,actorId));
	}
	return FString();
}