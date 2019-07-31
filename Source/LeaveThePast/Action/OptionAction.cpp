#include "OptionAction.h"
#include "../Manager/UIManager.h"
#include "../Manager/LogManager.h"

void UOptionItemAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("text"))
		{
			optionText = attributeValue;
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
	UMultiplyAction::Load(xmlNode);
}

FString UOptionItemAction::GetOptionText()
{
	return optionText;
}

void UOptionAction::Load(FXmlNode* xmlNode)
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
		if (nodeName == TEXT("OptionItem"))
		{
			UOptionItemAction* optionItem = NewObject<UOptionItemAction>();
			optionItem->Load(childNode);
			optionItemList.Add(optionItem);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知节点:%s！"), *actionName, *nodeName));
		}
	}
}

void UOptionAction::Update()
{
	if (!isCompleted && selectItemIndex!=-1)
	{
		if (optionItemList[selectItemIndex]->GetIsCompleted())
		{
			selectItemIndex = -1;
			Finish();
		}
		else
		{
			optionItemList[selectItemIndex]->Update();
		}
	}
}

FString UOptionAction::ExecuteReal()
{
	selectItemIndex = -1;

	UUIManager::GetInstance()->ShowOptionUI(this);
	return FString();
}

TArray<UOptionItemAction*> UOptionAction::GetOptionItemList()
{
	return optionItemList;
}

void UOptionAction::SetSelectItemIndex(int itemIndex)
{
	selectItemIndex = itemIndex;
	UUIManager::GetInstance()->HideOptionUI();
	optionItemList[selectItemIndex]->Execute();
}

bool UOptionAction::SkipAction()
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
		skipResult = optionItemList[selectItemIndex]->SkipAction();
	}
	if (!skipResult)
	{
		LogNormal(FString::Printf(TEXT("指令:%s不可跳过！"), *actionName));
	}
	return skipResult;
}
