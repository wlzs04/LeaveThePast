#include "../../Public/Script/Paragraph.h"
#include "../../Public/Manager/MainGameManager.h"
#include "Engine/World.h"

void UParagraph::Update()
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

void UParagraph::Load(FXmlNode* xmlNode)
{
	UMainGameManager* gameManager = ((UMainGameManager*)(GWorld->GetGameInstance()));
	for (auto childNode : xmlNode->GetChildrenNodes())
	{
		UActionBase* actionBase = gameManager->GetIegalActionByName(childNode->GetTag());

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

bool UParagraph::GetIsCompleted()
{
	return isCompleted;
}

void UParagraph::Start()
{
	currentActionIndex = 0;
	isStart = true;
	isCompleted = false;
	actionList[currentActionIndex]->Execute();
}