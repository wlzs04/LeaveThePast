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

void UAddCanControlActorAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			actorInfoId = FCString::Atoi(*attributeValue);
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
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

