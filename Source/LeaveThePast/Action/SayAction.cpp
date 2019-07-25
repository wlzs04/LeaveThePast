#include "SayAction.h"
#include "../Actor/ActorBase.h"
#include "../Manager/MainGameManager.h"
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
	UActionBase::Load(xmlNode);
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("text"))
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
	if (isCompleted == false && GetExecuteActor() != nullptr)
	{
		currentTime += GWorld->DeltaTimeSeconds;
		if (currentTime - startTime < actionTime)
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
	if (GetExecuteActor() != nullptr)
	{
		GetExecuteActor()->StartTalk();
	}
	startTime = GWorld->GetTimeSeconds();
	currentTime = GWorld->GetTimeSeconds();
	isCompleted = false;
	UUIManager::GetInstance()->ShowTalkUI(text, GetExecuteActor()->GetActorInfo()->GetActorName(),actionTime, GetExecuteActor()->GetActorInfo()->GetHeadImagePath());
	return FString();
}

void USayAction::Finish()
{
	if (GetExecuteActor() != nullptr)
	{
		GetExecuteActor()->StopTalk();
	}
	isCompleted = true;
}
