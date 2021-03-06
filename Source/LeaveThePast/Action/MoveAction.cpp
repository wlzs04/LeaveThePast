#include "MoveAction.h"
#include "..\Actor\ActorBase.h"
#include "../Actor/DirectorActor.h"
#include "..\Manager\ActorManager.h"
#include "..\Manager\ScriptManager.h"
#include "..\Manager\HelpManager.h"
#include "..\Manager\LogManager.h"

void UMoveAction::Load(FXmlNode* xmlNode)
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
		else if(attributeName == TEXT("direction"))
		{
			direction = UHelpManager::ConvertFStringToFVector(attributeValue);
		}
		else if (attributeName == TEXT("speed"))
		{
			speed = FCString::Atof(*attributeValue);
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

void UMoveAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			actorInfoId = FCString::Atoi(*attributeValue);
			isPlayerControlActorId = false;
			break;
		case 2:
			direction = UHelpManager::ConvertFStringToFVector(attributeValue);
			break;
		case 3:
			speed = FCString::Atof(*attributeValue);
			break;
		case 4:
			actionTime = FCString::Atof(*attributeValue);
			break;
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
		}
	}
}

void UMoveAction::Update()
{
	if (isCompleted==false)
	{
		float tickTime = UScriptManager::GetInstance()->GetScriptTickTime();
		currentTime += tickTime;
		if (currentTime < actionTime)
		{
			if (executeActor != nullptr)
			{
				FVector moveValue = direction * speed * tickTime;
				executeActor->AddMovementInput(direction * speed, tickTime);
				remainValue -= moveValue;
			}
		}
		else
		{
			Finish();
		}
	}
}

FString UMoveAction::ExecuteReal()
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
		LogError(FString::Printf(TEXT("指令：%s未找到actorInId：%d"), *actionName, actorInfoId));
	}
	currentTime = 0;
	remainValue = direction * speed;
	return FString();
}

void UMoveAction::FinishReal()
{
	if (executeActor != nullptr)
	{
		executeActor->AddActorWorldOffset(remainValue);
		executeActor = nullptr;
		remainValue = FVector::ZeroVector;
	}
}
