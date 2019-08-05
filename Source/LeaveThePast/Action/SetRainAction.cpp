#include "SetRainAction.h"
#include "../LeaveThePastGameModeBase.h"
#include "../Manager/LogManager.h"
#include "../Manager/MainGameManager.h"
#include "../Config/UserData.h"

void USetRainAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("rainValue"))
		{
			rainValue = FCString::Atoi(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void USetRainAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			rainValue = FCString::Atoi(*attributeValue);
			break;
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
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
	UMainGameManager::GetInstance()->GetUserData()->SetRainValue(rainValue);
	AActor* skyActor = ALeaveThePastGameModeBase::GetInstance()->GetSkyBPActor();
	UFunction* functionSetInfo = skyActor->FindFunction(TEXT("RefreshRain"));
	if (functionSetInfo)
	{
		skyActor->ProcessEvent(functionSetInfo, &rainValue);
	}
	else
	{
		LogError(FString::Printf(TEXT("指令:%s天空体没有方法RefreshRain。"), *actionName));
	}
	return FString();
}