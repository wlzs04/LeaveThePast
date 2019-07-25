#include "SetCloudyAction.h"
#include "../LeaveThePastGameModeBase.h"

USetCloudyAction::USetCloudyAction() :UActionBase()
{
	actionName = TEXT("SetCloudy");
}

void USetCloudyAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("cloudyValue"))
		{
			cloudyValue = FCString::Atof(*attributeValue);
		}
	}
}

void USetCloudyAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetCloudyAction::ExecuteReal()
{
	isCompleted = false;
	AActor* skActor = ALeaveThePastGameModeBase::GetInstance()->GetSkyBPActor();
	UFunction* functionSetInfo = skActor->FindFunction(TEXT("RefreshCloudy"));
	if (functionSetInfo)
	{
		skActor->ProcessEvent(functionSetInfo, &cloudyValue);
	}
	return FString();
}
