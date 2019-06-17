#include "DramaScriptManager.h"
#include "Engine/World.h"
#include <LeaveThePast\Public\Action\MoveAction.h>
#include <LeaveThePast\Public\Action\SayAction.h>
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "MainGameManager.h"

UDramaScriptManager::UDramaScriptManager() :UObject()
{
}

void UDramaScriptManager::StartDramaScriptMainByNameIndex(FString scriptName, int index)
{
	if (!dramaScriptMainMap.Contains(scriptName))
	{
		UE_LOG(LogLoad, Error, TEXT("未知剧本文件：%s"), *scriptName);
		return;
	}
	else if(currentScript!=nullptr && !currentScript->GetIsCompleted())
	{
		UE_LOG(LogLoad, Error, TEXT("当前已存在正在运行的剧本"));
		return;
	}
	else
	{
		currentScript = dramaScriptMainMap[scriptName];
		currentScript->Start();
		UE_LOG(LogLoad, Log, TEXT("剧本开始：%s"), *scriptName);
	}
}

void UDramaScriptManager::Tick()
{
	if (currentScript != nullptr)
	{
		if (currentScript->GetIsCompleted())
		{
			currentScript = nullptr;
			return;
		}
		else
		{
			currentScript->Update();
		}
	}
}

void UDramaScriptManager::LoadDramaScriptAll()
{
	LoadDramaScriptMain();
}

void UDramaScriptManager::LoadDramaScriptMain()
{
	FString dramaScriptMainRootPath = FPaths::ProjectContentDir() + dramaScriptMainRelativePath;
	//使用此方法查找文件时需要添加文件类型
	FString dramaScriptMainRootFilePath = dramaScriptMainRootPath + TEXT("*.*");
	TArray<FString> dramaScriptMainPaths;
	IFileManager::Get().FindFiles(dramaScriptMainPaths, *dramaScriptMainRootFilePath, true, false);

	for (auto var : dramaScriptMainPaths)
	{
		FString scriptPath = dramaScriptMainRootPath + var;
		UDramaScript* dramaScript = NewObject<UDramaScript>();
		dramaScript->Load(scriptPath);
		dramaScriptMainMap.Add(var.Left(var.Len()-4), dramaScript);
	}
}
