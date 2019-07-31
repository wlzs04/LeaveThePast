#include "RemoveCanControlActorAction.h"
#include "../Actor/DirectorActor.h"
#include "../Manager/LogManager.h"

void URemoveCanControlActorAction::Load(FXmlNode* xmlNode)
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

void URemoveCanControlActorAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString URemoveCanControlActorAction::ExecuteReal()
{
	ADirectorActor::GetInstance()->RemoveCanControlActorByInfoId(actorInfoId);
	return FString();
}