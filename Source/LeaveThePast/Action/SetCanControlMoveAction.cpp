#include "SetCanControlMoveAction.h"
#include "../Actor/DirectorActor.h"
#include "../Manager/LogManager.h"

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
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void USetCanControlMoveAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			canControlMove = FCString::ToBool(*attributeValue);
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
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