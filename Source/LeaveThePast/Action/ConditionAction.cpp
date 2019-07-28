#include "ConditionAction.h"
#include "../Manager/LogManager.h"
#include "../Manager/ScriptManager.h"

UConditionItemAction::UConditionItemAction() :UMultiplyAction()
{
	actionName = TEXT("ConditionItem");
}

void UConditionItemAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("type"))
		{
			if (attributeValue == TEXT("="))
			{
				conditionType = ConditionType::Equal;
			}
			else if (attributeValue == TEXT(">"))
			{
				conditionType = ConditionType::More;
			}
			else if (attributeValue == TEXT("<"))
			{
				conditionType = ConditionType::Less;
			}
			else
			{
				LogError(FString::Printf(TEXT("ConditionType类型不匹配：%s"), *attributeValue));
			}
		}
		else if (attributeName == TEXT("value"))
		{
			conditionValue = attributeValue;
		}
		else if (attributeName == TEXT("isDefault"))
		{
			isDefault = FCString::ToBool(*attributeValue);
		}
	}
	UMultiplyAction::Load(xmlNode);
}

bool UConditionItemAction::CheckCondition(FString checkConditionValue)
{
	bool returnValue = false;
	switch (conditionType)
	{
	case ConditionType::Equal:
		returnValue = checkConditionValue == conditionValue;
		break;
	case ConditionType::More:

		returnValue = FCString::Atof(*checkConditionValue) > FCString::Atof(*conditionValue);
		break;
	case ConditionType::Less:
		returnValue = FCString::Atof(*checkConditionValue) < FCString::Atof(*conditionValue);
		break;
	default:
		break;
	}
	return returnValue || isDefault;
}

UConditionAction::UConditionAction() :UActionBase()
{
	actionName = TEXT("Condition");
}

void UConditionAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("action"))
		{
			actionString = attributeValue;
		}
	}
	for (auto childNode : xmlNode->GetChildrenNodes())
	{
		if (childNode->GetTag() == TEXT("ConditionItem"))
		{
			UConditionItemAction* conditionItem = NewObject<UConditionItemAction>();
			conditionItem->Load(childNode);
			conditionItemList.Add(conditionItem);
		}
	}
}

void UConditionAction::Update()
{
	if (!isCompleted && selectConditionItemAction != nullptr)
	{
		if (selectConditionItemAction->GetIsCompleted())
		{
			Finish();
		}
		else
		{
			selectConditionItemAction->Update();
		}
	}
}

FString UConditionAction::ExecuteReal()
{
	FString conditionValue = UScriptManager::GetInstance()->ExecuteAction(actionString);

	for(UConditionItemAction* conditionItem : conditionItemList)
	{
		if (conditionItem->CheckCondition(conditionValue))
		{
			selectConditionItemAction = conditionItem;
		}
	}
	if (selectConditionItemAction != nullptr)
	{
		return selectConditionItemAction->Execute();
	}
	else
	{
		LogError(FString::Printf(TEXT("条件指令：%s没有符合项。"),*actionString));
	}
	return FString();
}

bool UConditionAction::SkipAction()
{
	bool skipResult = false;
	if (!isStart)
	{
		Execute();
	}
	if (selectConditionItemAction == nullptr)
	{
		return true;
	}
	return selectConditionItemAction->SkipAction();
}