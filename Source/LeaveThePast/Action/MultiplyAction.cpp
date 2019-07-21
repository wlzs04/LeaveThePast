#include "MultiplyAction.h"
#include "../Manager/ScriptManager.h"

void UMultiplyAction::Load(FXmlNode* xmlNode)
{
	UScriptManager* scriptManager = UScriptManager::GetInstance();
	for (auto childNode : xmlNode->GetChildrenNodes())
	{
		UActionBase* actionBase = scriptManager->GetIegalActionByName(childNode->GetTag());

		if (actionBase != nullptr)
		{
			UActionBase* actionBase2 = NewObject<UActionBase>((UObject*)GetTransientPackage(), actionBase->GetClass());
			actionBase2->Load(childNode);
			actionList.Add(actionBase2);
		}
		else
		{
			UE_LOG(LogLoad, Error, TEXT("未知指令：%s"), *childNode->GetTag());
		}
	}
}

void UMultiplyAction::Update()
{
	if (isStart)
	{
		if (currentActionIndex >= actionList.Num())
		{
			isStart = false;
			isCompleted = true;
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
				isStart = false;
				isCompleted = true;

				return;
			}
			actionList[currentActionIndex]->Execute();
			return;
		}
	}
}

void UMultiplyAction::ExecuteReal()
{
	isStart = true;
	isCompleted = false;
	currentActionIndex = 0;
	actionList[currentActionIndex]->Execute();
}
