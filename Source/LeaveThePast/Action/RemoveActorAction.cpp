#include "RemoveActorAction.h"
#include "../Manager/ActorManager.h"

URemoveActorAction::URemoveActorAction() :UActionBase()
{
	actionName = TEXT("NewActor");
}

void URemoveActorAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);

	for(auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("actorId"))
		{
			actorInfoId = FCString::Atoi(*attributeValue);
		}
	}
}

void URemoveActorAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString URemoveActorAction::ExecuteReal()
{
	isCompleted = false;
	UActorManager::GetInstance()->RemoveActorByInfoId(actorInfoId);
	return FString();
}