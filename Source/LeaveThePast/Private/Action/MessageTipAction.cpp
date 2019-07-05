#include "../../Public/Action/MessageTipAction.h"
#include "../../Public/Actor/ActorBase.h"
#include "../../Public/Manager/MainGameManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

UMessageTipAction::UMessageTipAction() :UActionBase()
{
	actionName = TEXT("Say");
}

void UMessageTipAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);
	for (auto attribute:xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("text"))
		{
			text = attributeValue;
		}
		else if(attributeName == TEXT("actionTime"))
		{
			actionTime = FCString::Atof(*attributeValue);
		}
	}
}

void UMessageTipAction::Update()
{
	if (isCompleted == false && GetExecuteActor() != nullptr)
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

void UMessageTipAction::ExecuteReal()
{
	startTime = GWorld->GetTimeSeconds();
	currentTime = GWorld->GetTimeSeconds();
	isCompleted = false;
	((UMainGameManager*)(GWorld->GetGameInstance()))->AddMessageTip(text);
}

