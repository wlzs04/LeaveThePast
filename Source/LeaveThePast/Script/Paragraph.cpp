#include "Paragraph.h"
#include "../Manager/MainGameManager.h"
#include "../Actor/DirectorActor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

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

				ADirectorActor::GetInstance()->SetCanControlMove(true);
				ADirectorActor::GetInstance()->SetCanControlView(true);

				return;
			}
			actionList[currentActionIndex]->Execute();
			return;
		}
	}
}

void UParagraph::Load(FXmlNode* xmlNode)
{
	UScriptManager* scriptManager = UScriptManager::GetInstance();
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		if (attribute.GetTag() == TEXT("id"))
		{
			paragraphId = FCString::Atoi(*attribute.GetValue());
		}
		else if (attribute.GetTag() == TEXT("canControlMove"))
		{
			canControlMove = FCString::ToBool(*attribute.GetValue());
		}
		else if (attribute.GetTag() == TEXT("canControlView"))
		{
			canControlView = FCString::ToBool(*attribute.GetValue());
		}
	}
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

bool UParagraph::GetIsCompleted()
{
	return isCompleted;
}

int UParagraph::GetParagraphId()
{
	return paragraphId;
}

void UParagraph::Start()
{
	currentActionIndex = 0;
	isStart = true;
	isCompleted = false;

	ADirectorActor::GetInstance()->SetCanControlMove(canControlMove);
	ADirectorActor::GetInstance()->SetCanControlView(canControlView);

	actionList[currentActionIndex]->Execute();
}

bool UParagraph::SkipScript()
{
	LogNormal(TEXT("开始跳过剧情！"));
	for (; currentActionIndex < actionList.Num(); currentActionIndex++)
	{
		if (!actionList[currentActionIndex]->SkipAction())
		{
			return false;
		}
	}
	isStart = false;
	isCompleted = true;
	ADirectorActor::GetInstance()->SetCanControlMove(true);
	ADirectorActor::GetInstance()->SetCanControlView(true);
	LogNormal(TEXT("已经跳过可跳过剧情！"));
	return true;
}
