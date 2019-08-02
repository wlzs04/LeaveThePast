#include "RandomAction.h"
#include "../Manager/LogManager.h"

void URandomItemAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("probability"))
		{
			probability = FCString::Atof(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
	UMultiplyAction::Load(xmlNode);
}

float URandomItemAction::GetProbability()
{
	return probability;
}

void URandomAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
	}
	for (auto childNode : xmlNode->GetChildrenNodes())
	{
		FString nodeName = childNode->GetTag();
		if (nodeName == TEXT("RandomItem"))
		{
			URandomItemAction* randomItem = NewObject<URandomItemAction>();
			randomItem->Load(childNode);
			randomItemList.Add(randomItem);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知节点:%s！"), *actionName, *nodeName));
		}
	}
}

void URandomAction::Update()
{
	if (!isCompleted && selectItemIndex != -1)
	{
		if (randomItemList[selectItemIndex]->GetIsCompleted())
		{
			selectItemIndex = -1;
			Finish();
		}
		else
		{
			randomItemList[selectItemIndex]->Update();
		}
	}
}

FString URandomAction::ExecuteReal()
{
	selectItemIndex = 0;

	float totalProbability = 0;
	for (auto var:randomItemList)
	{
		totalProbability += var->GetProbability();
	}

	 float resultValue =  FMath::RandRange(0.0f, totalProbability);
	 float minValue = 0;
	 float itemValue = 0;
	 for (int i = 0;i< randomItemList.Num();i++)
	 {
		 itemValue = randomItemList[i]->GetProbability();
		 if (resultValue>minValue&& resultValue< minValue+ itemValue)
		 {
			 selectItemIndex = i;
			 break;
		 }
		 minValue += itemValue;
	 }

	randomItemList[selectItemIndex]->Execute();

	return FString();
}

TArray<URandomItemAction*> URandomAction::GetRandomItemList()
{
	return randomItemList;
}

bool URandomAction::SkipAction()
{
	bool skipResult = false;
	if (!isStart)
	{
		Execute();
	}
	else if (isStart && selectItemIndex == -1)
	{
	}
	else
	{
		skipResult = randomItemList[selectItemIndex]->SkipAction();
	}
	if (!skipResult)
	{
		LogNormal(FString::Printf(TEXT("指令:%s不可跳过！"), *actionName));
	}
	return skipResult;
}
