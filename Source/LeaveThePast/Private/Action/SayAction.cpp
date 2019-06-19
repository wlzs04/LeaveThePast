#include "..\..\Public\Action\SayAction.h"
#include "..\..\Public\Actor\ActorBase.h"
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

	text = xmlNode->GetAttribute(TEXT("text"));
	voicePath = xmlNode->GetAttribute(TEXT("voicePath"));

	FString actionTimeString = xmlNode->GetAttribute(TEXT("actionTime"));
	actionTime = FCString::Atof(*actionTimeString);
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, text);
}


