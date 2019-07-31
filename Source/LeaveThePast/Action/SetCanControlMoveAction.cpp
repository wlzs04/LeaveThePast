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