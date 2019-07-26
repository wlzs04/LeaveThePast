#include "SayAction.h"
#include "../Actor/ActorBase.h"
#include "..\Manager\ActorManager.h"
#include "..\Manager\LogManager.h"
#include "..\Manager\ScriptManager.h"
#include "../Manager/UIManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

USayAction::USayAction() :UActionBase()
{
	actionName = TEXT("Say");
}

void USayAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("actorId"))
		{
			actorInfoId = FCString::Atoi(*attributeValue);
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
	}
}

void USayAction::Update()
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

FString USayAction::ExecuteReal()
{
	executeActor = UActorManager::GetInstance()->GetActorByInfoId(actorInfoId);
	if (executeActor == nullptr)
	{
		LogError(FString::Printf(TEXT("指令：Rotat未找到actorInId：%d"), actorInfoId));
	}
	else
	{
		executeActor->StartTalk();
		UUIManager::GetInstance()->ShowTalkUI(text, executeActor->GetActorInfo()->GetActorName(), actionTime, executeActor->GetActorInfo()->GetHeadImagePath());
	}
	currentTime = 0;
	return FString();
}

void USayAction::Finish()
{
	UActionBase::Finish();
	if (executeActor != nullptr)
	{
		UUIManager::GetInstance()->HideTalkUI();
		executeActor->StopTalk();
		executeActor = nullptr;
	}
}
