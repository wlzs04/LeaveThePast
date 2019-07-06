#include "MoveAction.h"
#include "..\Actor\ActorBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

UMoveAction::UMoveAction() :UActionBase()
{
	actionName = TEXT("Move");
}

void UMoveAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);

	FString directionString = xmlNode->GetAttribute(TEXT("direction"));
	TArray<FString> directionStringArray;
	directionString.ParseIntoArray(directionStringArray, TEXT(","));
	direction = FVector(FCString::Atof(*directionStringArray[0]), FCString::Atof(*directionStringArray[1]), FCString::Atof(*directionStringArray[2]));

	FString speedString = xmlNode->GetAttribute(TEXT("speed"));
	speed = FCString::Atof(*speedString);

	FString actionTimeString = xmlNode->GetAttribute(TEXT("actionTime"));
	actionTime = FCString::Atof(*actionTimeString);
}

void UMoveAction::Update()
{
	if (isCompleted==false && GetExecuteActor() != nullptr)
	{
		currentTime = GWorld->GetTimeSeconds();
		if (currentTime - startTime < actionTime)
		{
			GetExecuteActor()->AddMovementInput(direction * speed, GWorld->DeltaTimeSeconds);
		}
		else
		{
			isCompleted = true;
		}
	}
}

void UMoveAction::ExecuteReal()
{
	startTime = GWorld->GetTimeSeconds();
	currentTime = GWorld->GetTimeSeconds();
	isCompleted = false;
}
