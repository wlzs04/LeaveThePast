#include "SetCanControlViewAction.h"
#include "../Actor/DirectorActor.h"
#include "../Manager/LogManager.h"

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
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void USetCanControlViewAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			canControlView = FCString::ToBool(*attributeValue);
			break;
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
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