#include "RotateAction.h"
#include "..\Actor\ActorBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

URotateAction::URotateAction()
{
	actionName = TEXT("Rotate");
}

void URotateAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);

	FString actionTimeString = xmlNode->GetAttribute(TEXT("actionTime"));
	actionTime = FCString::Atof(*actionTimeString);

	FString valueString = xmlNode->GetAttribute(TEXT("value"));
	value = FCString::Atof(*valueString);
}

void URotateAction::Update()
{
	if (isCompleted == false && GetExecuteActor() != nullptr)
	{
		currentTime = GWorld->GetTimeSeconds();
		if (currentTime - startTime < actionTime)
		{
			float speed = (value/ actionTime)* (currentTime - lastTime);
			GetExecuteActor()->AddActorLocalRotation(FRotator(0, speed, 0));
		}
		else
		{
			isCompleted = true;
		}
		lastTime = currentTime;
	}
}

void URotateAction::ExecuteReal()
{
	startTime = GWorld->GetTimeSeconds();
	currentTime = GWorld->GetTimeSeconds();
	lastTime = currentTime;
	isCompleted = false;
}
