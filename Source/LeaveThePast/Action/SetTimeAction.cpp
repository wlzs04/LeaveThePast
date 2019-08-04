#include "SetTimeAction.h"
#include "../Manager/HelpManager.h"
#include "../Manager/MainGameManager.h"
#include "../Manager/LogManager.h"
#include "../Config/UserData.h"

void USetTimeAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("time"))
		{
			FTimespan timespan = UHelpManager::ConvertFStringToFTimespan(attributeValue);
			timeData.SetTime(timespan.GetHours(), timespan.GetMinutes(), timespan.GetSeconds());
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void USetTimeAction::Load(TArray<FString> paramList)
{
	if (paramList.Num() > 1)
	{
		FTimespan timespan = UHelpManager::ConvertFStringToFTimespan(paramList[1]);
		timeData.SetTime(timespan.GetHours(), timespan.GetMinutes(), timespan.GetSeconds());
	}
}

void USetTimeAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetTimeAction::ExecuteReal()
{
	UMainGameManager::GetInstance()->GetUserData()->SetGameTime(timeData.GetHours(), timeData.GetMinutes(), timeData.GetSeconds());
	return FString();
}