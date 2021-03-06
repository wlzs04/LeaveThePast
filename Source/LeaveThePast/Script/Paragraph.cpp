#include "Paragraph.h"
#include "../Manager/MainGameManager.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/UIManager.h"
#include "../Action/ActionBase.h"
#include "../Manager/LogManager.h"
#include "XmlParser/Public/XmlFile.h"
#include "../Actor/DirectorActor.h"

void UParagraph::Update()
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

void UParagraph::Load(FXmlNode* xmlNode)
{
	UScriptManager* scriptManager = UScriptManager::GetInstance();
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("id"))
		{
			paragraphId = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("canControlMove"))
		{
			canControlMove = FCString::ToBool(*attributeValue);
			needCanControlMove = true;
		}
		else if (attributeName == TEXT("canControlView"))
		{
			canControlView = FCString::ToBool(*attributeValue);
			needCanControlView = true;
		}
		else if (attributeName == TEXT("hideMainUI"))
		{
			hideMainUI = FCString::ToBool(*attributeValue);
			needHideMainUI = true;
		}
		else
		{
			LogWarning(FString::Printf(TEXT("Paragraph:%d中存在未知属性:%s：%s！"), paragraphId, *attributeName, *attributeValue));
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
			LogError(FString::Printf(TEXT("未知指令：%s"), *childNode->GetTag()));
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

bool UParagraph::Start()
{
	currentActionIndex = 0;
	isStart = true;
	isCompleted = false;

	if (needCanControlMove)
	{
		ADirectorActor::GetInstance()->SetCanControlMove(canControlMove);
	}
	if (needCanControlView)
	{
		ADirectorActor::GetInstance()->SetCanControlView(canControlView);
	}

	if (needHideMainUI)
	{
		UUIManager::GetInstance()->HideMainUI();
	}

	actionList[currentActionIndex]->Execute();
	return true;
}

bool UParagraph::Stop()
{
	if (isStart)
	{
		if (currentActionIndex >= actionList.Num())
		{
		}
		else if (!actionList[currentActionIndex]->GetIsCompleted())
		{
			actionList[currentActionIndex]->Finish();
		}
		Finish();
	}
	return true;
}

void UParagraph::Finish()
{
	isStart = false;
	isCompleted = true;
	currentActionIndex = 0;

	if (needCanControlMove)
	{
		ADirectorActor::GetInstance()->SetCanControlMove(!canControlMove);
	}
	if (needCanControlView)
	{
		ADirectorActor::GetInstance()->SetCanControlView(!canControlView);
	}
	if (needHideMainUI)
	{
		UUIManager::GetInstance()->ShowMainUI();
	}
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
	Finish();
	LogNormal(TEXT("已经跳过剧情！"));
	return true;
}

TArray<UActionBase*> UParagraph::GetActionList()
{
	return actionList;
}
