#include "AddCanControlActorAction.h"
#include "../Actor/DirectorActor.h"

UAddCanControlActorAction::UAddCanControlActorAction() :UActionBase()
{
	actionName = TEXT("AddCanControlActor");
}

void UAddCanControlActorAction::Load(FXmlNode* xmlNode)
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

void UAddCanControlActorAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UAddCanControlActorAction::ExecuteReal()
{
	isCompleted = false;
	ADirectorActor::GetInstance()->AddCanControlActorByInfoId(actorInfoId);
	return FString();
}

