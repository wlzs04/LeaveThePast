#include "MultiplyAction.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/LogManager.h"

void UMultiplyAction::Load(FXmlNode* xmlNode)
{
	UScriptManager* scriptManager = UScriptManager::GetInstance();
	for (auto childNode : xmlNode->GetChildrenNodes())
	{
		FString nodeName = childNode->GetTag();
		UActionBase* actionBase = scriptManager->GetIegalActionByName(nodeName);

		if (actionBase != nullptr)
		{
			UActionBase* actionBase2 = NewObject<UActionBase>((UObject*)GetTransientPackage(), actionBase->GetClass());
			actionBase2->Load(childNode);
			actionList.Add(actionBase2);
		}
		else
		{
			LogError(FString::Printf(TEXT("未知指令：%s"), *nodeName));
		}
	}
}

void UMultiplyAction::Update()
{
	if (isStart)
	{
		if (currentActionIndex >= actionList.Num())
		{
			Finish();
			return;
		}
		if (!actionList[currentActionIndex]->GetIsCompleted())
		{
			actionList[currentActionIndex]->Update();
			return;
		}
		else
		{
			currentActionIndex++;
			if (currentActionIndex >= actionList.Num())
			{
				Finish();

				return;
			}
			actionList[currentActionIndex]->Execute();
			return;
		}
	}
}

FString UMultiplyAction::ExecuteReal()
{
	currentActionIndex = 0;
	actionList[currentActionIndex]->Execute();
	return FString();
}

bool UMultiplyAction::SkipAction()
{
	for (; currentActionIndex < actionList.Num(); currentActionIndex++)
	{
		if (!actionList[currentActionIndex]->SkipAction())
		{
			return false;
		}
	}
	Finish();
	return true;
}
