#include "ChangeCameraActorAction.h"
#include "..\Manager\MainGameManager.h"
#include "..\Actor\DirectorActor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


UChangeCameraActorAction::UChangeCameraActorAction()
{
	actionName = TEXT("ChangeCameraActor");
}

void UChangeCameraActorAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("actorId"))
		{
			actorInfoId = FCString::Atoi(*attributeValue);
		}
	}
}

void UChangeCameraActorAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UChangeCameraActorAction::ExecuteReal()
{
	AActorBase* executeActor = UActorManager::GetInstance()->GetActorByInfoId(actorInfoId);
	if (executeActor != nullptr)
	{
		ADirectorActor::GetInstance()->SetControlActorById(executeActor->GetActorId());
	}
	else
	{
		LogError(FString::Printf(TEXT("指令：ChangeCameraActor没有找到演员InfoId：%d"), actorInfoId));
	}
	return FString();
}
