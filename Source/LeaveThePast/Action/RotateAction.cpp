#include "RotateAction.h"
#include "..\Actor\ActorBase.h"
#include "..\Manager\ActorManager.h"
#include "..\Manager\ScriptManager.h"
#include "..\Manager\LogManager.h"

URotateAction::URotateAction()
{
	actionName = TEXT("Rotate");
}

void URotateAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("actorId"))
		{
			actorInfoId = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("value"))
		{
			value = FCString::Atof(*attributeValue);
		}
		else if (attributeName == TEXT("actionTime"))
		{
			actionTime = FCString::Atof(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void URotateAction::Update()
{
	if (isCompleted == false)
	{
		currentTime += UScriptManager::GetInstance()->GetScriptTickTime();
		if (currentTime < actionTime)
		{
			if (executeActor != nullptr)
			{
				float speed = (value / actionTime) * (currentTime - lastTime);
				executeActor->AddActorLocalRotation(FRotator(0, speed, 0));
				remainValue -= speed;
			}
		}
		else
		{
			Finish();
		}
		lastTime = currentTime;
	}
}

FString URotateAction::ExecuteReal()
{
	executeActor = UActorManager::GetInstance()->GetActorByInfoId(actorInfoId);
	if (executeActor == nullptr)
	{
		LogError(FString::Printf(TEXT("指令：Rotate未找到actorInId：%d"), actorInfoId));
	}
	currentTime = 0;
	lastTime = 0;
	remainValue = value;
	return FString();
}

void URotateAction::FinishReal()
{
	if (executeActor != nullptr)
	{
		executeActor->AddActorLocalRotation(FRotator(0, remainValue, 0));
		executeActor = nullptr;
		remainValue = 0;
	}
}
