#include "RotateAction.h"
#include "..\Actor\ActorBase.h"
#include "../Actor/DirectorActor.h"
#include "..\Manager\ActorManager.h"
#include "..\Manager\ScriptManager.h"
#include "..\Manager\LogManager.h"

void URotateAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("actorId"))
		{
			actorInfoId = FCString::Atoi(*attributeValue);
			isPlayerControlActorId = false;
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

void URotateAction::Load(TArray<FString> paramList)
{
	if (paramList.Num() > 1)
	{
		actorInfoId = FCString::Atoi(*paramList[1]);
		isPlayerControlActorId = false;
	}
	if (paramList.Num() > 2)
	{
		value = FCString::Atof(*paramList[2]);
	}
	if (paramList.Num() > 3)
	{
		actionTime = FCString::Atof(*paramList[3]);
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
	if (isPlayerControlActorId)
	{
		executeActor = ADirectorActor::GetInstance()->GetCurrentControlActor();
	}
	else
	{
		executeActor = UActorManager::GetInstance()->GetActorByInfoId(actorInfoId);
	}
	if (executeActor == nullptr)
	{
		LogError(FString::Printf(TEXT("指令：%s未找到actorInId：%d"),*actionName, actorInfoId));
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
