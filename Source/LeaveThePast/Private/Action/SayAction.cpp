#include "..\..\Public\Action\SayAction.h"
#include "..\..\Public\Actor\ActorBase.h"
#include "../../Public/Manager/MainGameManager.h"
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
		currentTime = GWorld->GetTimeSeconds();
		if (currentTime - startTime < actionTime)
		{
			
		}
		else
		{
			if (GetExecuteActor() != nullptr)
			{
				GetExecuteActor()->StopTalk();
			}
			isCompleted = true;
		}
	}
}

void USayAction::ExecuteReal()
{
	if (GetExecuteActor() != nullptr)
	{
		GetExecuteActor()->StartTalk();
	}
	startTime = GWorld->GetTimeSeconds();
	currentTime = GWorld->GetTimeSeconds();
	isCompleted = false;
	((UMainGameManager*)(GWorld->GetGameInstance()))->SetTalkUI(text, GetExecuteActor()->GetActorInfo()->GetActorName(),actionTime);
}