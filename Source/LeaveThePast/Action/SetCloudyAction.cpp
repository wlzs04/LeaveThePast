#include "SetCloudyAction.h"
#include "../LeaveThePastGameModeBase.h"
#include "../Manager/LogManager.h"
#include "../Manager/MainGameManager.h"
#include "../Config/UserData.h"

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

void USetCloudyAction::Load(TArray<FString> paramList)
{
	if (paramList.Num() > 1)
	{
		cloudyValue = FCString::Atoi(*paramList[1]);
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
	UMainGameManager::GetInstance()->GetUserData()->SetCloudyValue(cloudyValue);
	AActor* skyActor = ALeaveThePastGameModeBase::GetInstance()->GetSkyBPActor();
	UFunction* functionSetInfo = skyActor->FindFunction(TEXT("RefreshCloudy"));
	if (functionSetInfo)
	{
		skyActor->ProcessEvent(functionSetInfo, &cloudyValue);
	}
	else
	{
		LogError(FString::Printf(TEXT("指令:%s天空体没有方法RefreshCloudy。"), *actionName));
	}
	return FString();
}
