#include "ScriptManager.h"
#include "Engine/World.h"

#include "../Action/MoveAction.h"
#include "../Action/SayAction.h"
#include "../Action/RotateAction.h"
#include "../Action/ChangeCameraActorAction.h"
#include "../Action/MessageTipAction.h"
#include "../Action/PlayBGMAction.h"
#include "../Action/AddItemAction.h"

#include "../Script/Chapter.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "MainGameManager.h"

UScriptManager* UScriptManager::scriptManager = nullptr;

UScriptManager* UScriptManager::GetInstance()
{
	return UScriptManager::scriptManager;
}

void UScriptManager::Init()
{
	UScriptManager::scriptManager = this;
	LoadAllIegalAction();
	LoadAllScript();
}

void UScriptManager::StartMainScriptByNameIndex(FString scriptName, int index)
{
	if (!mainChapterMap.Contains(scriptName))
	{
		LogError(FString::Printf(TEXT("未知剧本文件：%s"), *scriptName));
		return;
	}
	else if(currentScript!=nullptr && !currentScript->GetIsCompleted())
	{
		LogError(FString::Printf(TEXT("当前已存在正在运行的剧本")));
		return;
	}
	else
	{
		currentScript = mainChapterMap[scriptName];
		currentScript->Start();
		LogNormal(FString::Printf(TEXT("剧本开始：%s"), *scriptName));
	}
}

void UScriptManager::Tick()
{
	if (currentScript != nullptr)
	{
		if (currentScript->GetCurrentSection())
		{
			currentScript->Update();
		}
		else
		{
			currentScript = nullptr;
			return;
		}
	}
}

void UScriptManager::LoadAllScript()
{
	LoadMainScript();
	LoadSideScript();
	LoadSceneScript();
}

TMap<FString, UChapter*> UScriptManager::GetMainChapterMap()
{
	return mainChapterMap;
}

TMap<FString, UChapter*> UScriptManager::GetSideChapterMap()
{
	return sideChapterMap;
}

TMap<FString, UChapter*> UScriptManager::GetSceneChapterMap()
{
	return sceneChapterMap;
}

void UScriptManager::LoadMainScript()
{
	mainChapterMap.Empty();
	FString mainScriptMainRootPath = FPaths::ProjectContentDir() + mainScriptRelativePath;
	//使用此方法查找文件时需要添加文件类型
	FString mainScriptRootFilePath = mainScriptMainRootPath + TEXT("*.*");
	TArray<FString> mainScriptPaths;
	IFileManager::Get().FindFiles(mainScriptPaths, *mainScriptRootFilePath, true, false);

	for (auto var : mainScriptPaths)
	{
		FString scriptPath = mainScriptMainRootPath + var;
		UChapter* chapter = NewObject<UChapter>();
		chapter->Load(scriptPath);
		mainChapterMap.Add(var.Left(var.Len()-4), chapter);
	}
}

void UScriptManager::LoadSideScript()
{
	sideChapterMap.Empty();
	FString sideScriptMainRootPath = FPaths::ProjectContentDir() + sideScriptRelativePath;
	//使用此方法查找文件时需要添加文件类型
	FString sideScriptRootFilePath = sideScriptMainRootPath + TEXT("*.*");
	TArray<FString> sideScriptPaths;
	IFileManager::Get().FindFiles(sideScriptPaths, *sideScriptRootFilePath, true, false);

	for (auto var : sideScriptPaths)
	{
		FString scriptPath = sideScriptMainRootPath + var;
		UChapter* chapter = NewObject<UChapter>();
		chapter->Load(scriptPath);
		sideChapterMap.Add(var.Left(var.Len()-4), chapter);
	}
}

void UScriptManager::LoadSceneScript()
{
	sceneChapterMap.Empty();
	FString sceneScriptMainRootPath = FPaths::ProjectContentDir() + sceneScriptRelativePath;
	//使用此方法查找文件时需要添加文件类型
	FString sceneScriptRootFilePath = sceneScriptMainRootPath + TEXT("*.*");
	TArray<FString> sceneScriptPaths;
	IFileManager::Get().FindFiles(sceneScriptPaths, *sceneScriptRootFilePath, true, false);

	for (auto var : sceneScriptPaths)
	{
		FString scriptPath = sceneScriptMainRootPath + var;
		UChapter* chapter = NewObject<UChapter>();
		chapter->Load(scriptPath);
		sceneChapterMap.Add(var.Left(var.Len()-4), chapter);
	}
}

void UScriptManager::LoadAllIegalAction()
{
	AddIegalAction(NewObject<UMoveAction>(this));
	AddIegalAction(NewObject<USayAction>(this));
	AddIegalAction(NewObject<URotateAction>(this));
	AddIegalAction(NewObject<UChangeCameraActorAction>(this));
	AddIegalAction(NewObject<UMessageTipAction>(this));
	AddIegalAction(NewObject<UPlayBGMAction>(this));
	AddIegalAction(NewObject<UAddItemAction>(this));
}

void UScriptManager::AddIegalAction(UActionBase* actionBase)
{
	legalActionMap.Add(actionBase->GetActionName(), actionBase);
}

UActionBase* UScriptManager::GetIegalActionByName(FString actionName)
{
	if (legalActionMap.Contains(actionName))
	{
		return legalActionMap[actionName];
	}
	return nullptr;
}

void UScriptManager::ExecuteAction(FString actionValue)
{
	if (actionValue.IsEmpty())
	{
		return;
	}
	TArray<FString> stringArray;
	actionValue.ParseIntoArray(stringArray, TEXT(" "));
	if (stringArray.Num() > 0)
	{
		UActionBase* actionBase = GetIegalActionByName(stringArray[0]);
		if (actionBase != nullptr)
		{
			UActionBase* actionBase2 = NewObject<UActionBase>(this, actionBase->GetClass());
			actionBase2->Load(stringArray);
			actionBase2->Execute();
		}
		else
		{
			LogError(stringArray[0] + TEXT("指令不合法！"));
		}
	}
}