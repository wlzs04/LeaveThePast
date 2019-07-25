#include "OptionAction.h"
#include "../Manager/UIManager.h"
#include "../Manager/LogManager.h"

UOptionItemAction::UOptionItemAction() :UMultiplyAction()
{
	actionName = TEXT("OptionItem");
}

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
	}
	UMultiplyAction::Load(xmlNode);
}

FString UOptionItemAction::GetOptionText()
{
	return optionText;
}

UOptionAction::UOptionAction() :UActionBase()
{
	actionName = TEXT("Option");
}

void UOptionAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);
	for (auto childNode : xmlNode->GetChildrenNodes())
	{
		if (childNode->GetTag() == TEXT("OptionItem"))
		{
			UOptionItemAction* optionItem = NewObject<UOptionItemAction>();
			optionItem->Load(childNode);
			optionItemList.Add(optionItem);
		}
	}
}

void UOptionAction::Update()
{
	if (!isCompleted && selectItemIndex!=-1)
	{
		if (optionItemList[selectItemIndex]->GetIsCompleted())
		{
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
	isCompleted = false;
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
	LogNormal(FString::Printf(TEXT("指令:%s不可跳过！"),*actionName));
	return false;
}
