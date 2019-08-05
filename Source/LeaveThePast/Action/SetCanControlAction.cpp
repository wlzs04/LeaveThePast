#include "SetCanControlAction.h"
#include "../Actor/DirectorActor.h"
#include "../Manager/LogManager.h"

void USetCanControlAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("canControl"))
		{
			canControl = FCString::ToBool(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void USetCanControlAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			canControl = FCString::ToBool(*attributeValue);
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
		}
	}
}

void USetCanControlAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetCanControlAction::ExecuteReal()
{
	ADirectorActor::GetInstance()->SetCanControl(canControl);
	return FString();
}