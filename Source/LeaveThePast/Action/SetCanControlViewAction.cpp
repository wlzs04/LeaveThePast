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