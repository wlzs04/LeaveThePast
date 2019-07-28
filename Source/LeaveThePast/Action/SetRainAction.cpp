#include "SetRainAction.h"
#include "../LeaveThePastGameModeBase.h"

USetRainAction::USetRainAction() :UActionBase()
{
	actionName = TEXT("SetRain");
}

void USetRainAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("rainFallValue"))
		{
			rainFallValue = FCString::Atoi(*attributeValue);
		}
	}
}

void USetRainAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetRainAction::ExecuteReal()
{
	AActor* skActor = ALeaveThePastGameModeBase::GetInstance()->GetSkyBPActor();
	UFunction* functionSetInfo = skActor->FindFunction(TEXT("RefreshRain"));
	if (functionSetInfo)
	{
		skActor->ProcessEvent(functionSetInfo, &rainFallValue);
	}
	return FString();
}