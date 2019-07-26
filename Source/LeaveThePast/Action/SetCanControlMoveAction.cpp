#include "SetCanControlMoveAction.h"
#include "../Actor/DirectorActor.h"

USetCanControlMoveAction::USetCanControlMoveAction() :UActionBase()
{
	actionName = TEXT("SetCanControlMove");
}

void USetCanControlMoveAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("canControlMove"))
		{
			canControlMove = FCString::ToBool(*attributeValue);
		}
	}
}

void USetCanControlMoveAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetCanControlMoveAction::ExecuteReal()
{
	ADirectorActor::GetInstance()->SetCanControlMove(canControlMove);
	return FString();
}