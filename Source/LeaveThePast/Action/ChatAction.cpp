#include "ChatAction.h"
#include "../Actor/ActorBase.h"
#include "../Actor/DirectorActor.h"
#include "../Manager/ActorManager.h"
#include "../Manager/LogManager.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/UIManager.h"

void UChatAction::Load(FXmlNode* xmlNode)
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
		else if (attributeName == TEXT("text"))
		{
			text = attributeValue;
		}
		else if (attributeName == TEXT("voicePath"))
		{
			voicePath = attributeValue;
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

void UChatAction::Update()
{
	if (isCompleted == false)
	{
		currentTime += UScriptManager::GetInstance()->GetScriptTickTime();
		if (currentTime < actionTime)
		{

		}
		else
		{
			Finish();
		}
	}
}

FString UChatAction::ExecuteReal()
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
	else
	{
		executeActor->StartTalk();
		UUIManager::GetInstance()->ShowTalkUI(text, executeActor->GetActorInfo()->GetActorName(), actionTime, executeActor->GetActorInfo()->GetHeadImagePath());
	}
	currentTime = 0;
	return FString();
}

void UChatAction::FinishReal()
{
	if (executeActor != nullptr)
	{
		UUIManager::GetInstance()->HideTalkUI();
		executeActor->StopTalk();
		executeActor = nullptr;
	}
}
