#include "..\..\Public\Script\DramaScript.h"
#include "Engine/World.h"
#include "..\..\Public\Manager\MainGameManager.h"

void UDramaScript::Update()
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

void UDramaScript::Load(FString newScriptPath)
{
	scriptPath = newScriptPath;
	FXmlFile* xmlFile = new FXmlFile(scriptPath); 
	if (!xmlFile->IsValid())
	{
		UE_LOG(LogLoad, Error, TEXT("dramaScriptMainPath文件加载失败：%s"), *scriptPath);
		return;
	}
	UMainGameManager* gameManager = ((UMainGameManager*)(GWorld->GetGameInstance()));
	FXmlNode* rootNode = xmlFile->GetRootNode();
	for (auto childNode : rootNode->GetChildrenNodes())
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
	xmlFile->Clear();
	delete xmlFile;
	UE_LOG(LogLoad, Log, TEXT("DramaScript文件：%s加载完成！"), *scriptPath);
}

bool UDramaScript::GetIsCompleted()
{
	return isCompleted;
}

void UDramaScript::Start()
{
	currentActionIndex = 0;
	isStart = true;
	isCompleted = false;
	actionList[currentActionIndex]->Execute();
}
