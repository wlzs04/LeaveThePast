#include "AddCanControlActorAction.h"
#include "../Actor/DirectorActor.h"
#include "../Manager/LogManager.h"

void UAddCanControlActorAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("actorId"))
		{
			actorInfoId = FCString::Atoi(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void UAddCanControlActorAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UAddCanControlActorAction::ExecuteReal()
{
	ADirectorActor::GetInstance()->AddCanControlActorByInfoId(actorInfoId);
	return FString();
}

