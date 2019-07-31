#include "SetActorInfoAction.h"
#include "../Manager/ActorManager.h"
#include "../Manager/LogManager.h"
#include "../Actor/ActorBase.h"
#include "../Manager/HelpManager.h"

void USetActorInfoAction::Load(FXmlNode* xmlNode)
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

void USetActorInfoAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetActorInfoAction::ExecuteReal()
{
	AActorBase* actor = UActorManager::GetInstance()->GetActorByInfoId(actorId);
	if (actor != nullptr)
	{
		if (needReplacePosition)
		{
			actor->SetActorLocation(position);
		}
		if (needReplaceRotation)
		{
			actor->SetActorRotation(rotation);
		}
	}
	else
	{
		LogError(FString::Printf(TEXT("指令：%s场景中不存在指定演员%d。"), *actionName, actorId));
	}
	
	return FString();
}
