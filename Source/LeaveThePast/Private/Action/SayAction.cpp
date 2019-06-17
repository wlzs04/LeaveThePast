#include "..\..\Public\Action\SayAction.h"
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
	if (isCompleted == false && currentPlayer != nullptr)
	{
		currentTime = GWorld->GetTimeSeconds();
		if (currentTime - startTime < actionTime)
		{
			
		}
		else
		{
			isCompleted = true;
		}
	}
}

void USayAction::ExecuteReal()
{
	currentPlayer = GWorld->GetFirstPlayerController()->GetPawn();
	startTime = GWorld->GetTimeSeconds();
	currentTime = GWorld->GetTimeSeconds();
	isCompleted = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, text);
}


