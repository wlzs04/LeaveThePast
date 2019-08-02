#include "ConditionAction.h"
#include "../Manager/LogManager.h"
#include "../Manager/ScriptManager.h"

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
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
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
		if (!isDefault)
		{
			LogError(FString::Printf(TEXT("%s指令并未标记为默认，使用的判断类型:%d未写具体判断方法！"), *actionName, conditionType));
		}
		break;
	}
	return returnValue || isDefault;
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
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
	for (auto childNode : xmlNode->GetChildrenNodes())
	{
		FString nodeName = childNode->GetTag();
		if (nodeName == TEXT("ConditionItem"))
		{
			UConditionItemAction* conditionItem = NewObject<UConditionItemAction>();
			conditionItem->Load(childNode);
			conditionItemList.Add(conditionItem);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知节点:%s！"), *actionName, *nodeName));
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
	FString conditionValue = UScriptManager::GetInstance()->ExecuteActionString(actionString);

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
