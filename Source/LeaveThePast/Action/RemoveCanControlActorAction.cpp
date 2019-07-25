#include "RemoveCanControlActorAction.h"
#include "../Actor/DirectorActor.h"

URemoveCanControlActorAction::URemoveCanControlActorAction() :UActionBase()
{
	actionName = TEXT("RemoveCanControlActor");
}

void URemoveCanControlActorAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);

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

void URemoveCanControlActorAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString URemoveCanControlActorAction::ExecuteReal()
{
	isCompleted = false;
	ADirectorActor::GetInstance()->RemoveCanControlActorByInfoId(actorInfoId);
	return FString();
}