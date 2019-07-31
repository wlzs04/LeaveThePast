#include "SetCloudyAction.h"
#include "../LeaveThePastGameModeBase.h"
#include "../Manager/LogManager.h"

void USetCloudyAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("cloudyValue"))
		{
			cloudyValue = FCString::Atof(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
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
	AActor* skActor = ALeaveThePastGameModeBase::GetInstance()->GetSkyBPActor();
	UFunction* functionSetInfo = skActor->FindFunction(TEXT("RefreshCloudy"));
	if (functionSetInfo)
	{
		skActor->ProcessEvent(functionSetInfo, &cloudyValue);
	}
	return FString();
}
