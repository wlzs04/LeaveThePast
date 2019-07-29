#include "SetCanControlAction.h"
#include "../Actor/DirectorActor.h"
#include "../Manager/LogManager.h"

USetCanControlAction::USetCanControlAction() :UActionBase()
{
	actionName = TEXT("SetCanControl");
}

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