#include "MessageTipAction.h"
#include "../Actor/ActorBase.h"
#include "../Manager/MainGameManager.h"
#include "../Manager/UIManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

UMessageTipAction::UMessageTipAction() :UActionBase()
{
	actionName = TEXT("MessageTip");
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
	if (isCompleted == false)
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
	UUIManager::GetInstance()->AddMessageTip(text);
}

