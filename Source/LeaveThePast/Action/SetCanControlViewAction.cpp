#include "SetCanControlViewAction.h"
#include "../Actor/DirectorActor.h"

USetCanControlViewAction::USetCanControlViewAction() :UActionBase()
{
	actionName = TEXT("SetCanControlView");
}

void USetCanControlViewAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("canControlView"))
		{
			canControlView = FCString::ToBool(*attributeValue);
		}
	}
}

void USetCanControlViewAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetCanControlViewAction::ExecuteReal()
{
	ADirectorActor::GetInstance()->SetCanControlView(canControlView);
	return FString();
}