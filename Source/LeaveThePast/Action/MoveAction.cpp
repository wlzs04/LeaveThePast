#include "MoveAction.h"
#include "..\Actor\ActorBase.h"
#include "..\Manager\ActorManager.h"
#include "..\Manager\ScriptManager.h"
#include "..\Manager\HelpManager.h"
#include "..\Manager\LogManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

UMoveAction::UMoveAction() :UActionBase()
{
	actionName = TEXT("Move");
}

void UMoveAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("actorId"))
		{
			actorInfoId = FCString::Atoi(*attributeValue);
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
	}
}

void UMoveAction::Update()
{
	if (isCompleted==false)
	{
		currentTime += UScriptManager::GetInstance()->GetScriptTickTime();
		if (currentTime < actionTime)
		{
			if (executeActor != nullptr)
			{
				FVector moveValue = direction * speed * GWorld->DeltaTimeSeconds;
				executeActor->AddMovementInput(direction * speed, GWorld->DeltaTimeSeconds);
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
	executeActor = UActorManager::GetInstance()->GetActorByInfoId(actorInfoId);
	if (executeActor == nullptr)
	{
		LogError(FString::Printf(TEXT("指令：Move未找到actorInId：%d"), actorInfoId));
	}
	currentTime = 0;
	remainValue = direction * speed;
	return FString();
}

void UMoveAction::Finish()
{
	UActionBase::Finish();
	if (executeActor != nullptr)
	{
		executeActor->AddActorWorldOffset(remainValue);
		executeActor = nullptr;
		remainValue = FVector::ZeroVector;
	}
}
