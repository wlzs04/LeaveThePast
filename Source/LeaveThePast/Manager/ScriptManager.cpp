#include "ScriptManager.h"

#include "../Action/MoveAction.h"
#include "../Action/SayAction.h"
#include "../Action/RotateAction.h"
#include "../Action/ChangeControlActorAction.h"
#include "../Action/MessageTipAction.h"
#include "../Action/PlayBGMAction.h"
#include "../Action/AddItemAction.h"
#include "../Action/AddActorAction.h"
#include "../Action/RemoveMoneyAction.h"
#include "../Action/OptionAction.h"

#include "../Action/RemoveActorAction.h"
#include "../Action/SetActorInfoAction.h"
#include "../Action/AddCanControlActorAction.h"
#include "../Action/RemoveCanControlActorAction.h"
#include "../Action/AddNextScriptAction.h"
#include "../Action/SetCanControlAction.h"
#include "../Action/SetTimeAction.h"
#include "../Action/SetRainAction.h"
#include "../Action/SetCloudyAction.h"
#include "../Action/AddScriptVolumeAction.h"
#include "../Action/ConditionAction.h"
#include "../Action/GetItemNumberAction.h"
#include "../Action/GetMoneyAction.h"
#include "../Action/SetScriptActorAction.h"
#include "../Action/SetCanControlMoveAction.h"
#include "../Action/SetCanControlViewAction.h"
#include "../Action/SetScriptExecuteSpeedAction.h"
#include "../Action/RemoveScriptVolumeAction.h"
#include "../Action/ClearScriptActorAction.h"
#include "../Action/SetChapterStateAction.h"
#include "../Action/SetSectionStateAction.h"
#include "../Action/SetParagraphStateAction.h"
#include "../Action/SetMainUIStateAction.h"
#include "../Action/StopScriptAction.h"
#include "../Action/RemoveNextScriptAction.h"

#include "../Script/Chapter.h"
#include "../Script/Section.h"
#include "../Script/Paragraph.h"
#include "../Config/UserData.h"
#include "MainGameManager.h"
#include "LogManager.h"
#include "UIManager.h"

#include "Engine/World.h"

#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/HAL/FileManager.h"

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

void UScriptManager::StartScript(FString scriptName, int sectionId, int paragrapgId)
{
	if (!mainChapterMap.Contains(scriptName))
	{
		LogError(FString::Printf(TEXT("未知剧本文件：%s"), *scriptName));
		return;
	}
	else if(currentScript!=nullptr)
	{
		LogError(FString::Printf(TEXT("当前已存在正在运行的剧本:%s"), *currentScript->GetChapterName()));
		return;
	}
	else
	{
		currentScript = mainChapterMap[scriptName];
		LogNormal(FString::Printf(TEXT("剧本开始：%s,%d,%d"), *scriptName, sectionId, paragrapgId));
		UUserData* userData = UMainGameManager::GetInstance()->GetUserData();
		userData->SetParagraphState(scriptName, sectionId, paragrapgId,1);
		currentScript->Start(sectionId, paragrapgId);
	}
}

void UScriptManager::StartNextScript()
{
	UUserData* userData = UMainGameManager::GetInstance()->GetUserData();
	if (userData->GetNextScriptList().Num() > 0)
	{
		FScriptItemData scriptItemData = userData->GetNextScriptList()[0];
		userData->RemoveNextScript(scriptItemData);
		StartScript(scriptItemData.chapter, scriptItemData.sectionId, scriptItemData.paragraphId);
	}
}

void UScriptManager::StopCurrentScript()
{
	if (currentScript != nullptr)
	{
		FString currentScriptName = currentScript->GetChapterName();
		int currentSectionId = currentScript->GetCurrentSection()->GetSectionId();
		int currentParagraphId = currentScript->GetCurrentSection()->GetCurrentParagraph()->GetParagraphId();
		currentScript->GetCurrentSection()->GetCurrentParagraph()->Finish();
		LogNormal(FString::Printf(TEXT("剧本退出：%s,%d,%d"), *currentScriptName, currentSectionId, currentParagraphId));
		currentScript = nullptr;
		return;
	}
	else
	{
		LogWarning(TEXT("当前并没有执行剧本，为什么会调用到停止方法上？"));
	}
}

void UScriptManager::Tick()
{
	scriptTickTime = GetWorld()->DeltaTimeSeconds * scriptExecuteSpeed;
	if (currentScript != nullptr)
	{
		if (currentScript->GetCurrentSection())
		{
			currentScript->Update();
		}
		else
		{
			ScriptFinish();
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

UChapter* UScriptManager::GetCurrentChapter()
{
	return currentScript;
}

void UScriptManager::SkipScript()
{
	if (currentScript != nullptr)
	{
		bool skipResult = currentScript->GetCurrentSection()->GetCurrentParagraph()->SkipScript();
		if (skipResult)
		{
			ScriptFinish();
		}
	}
	else
	{
		LogWarning(TEXT("当前并没有执行剧本，为什么会调用到跳过方法上？"));
	}
}

bool UScriptManager::IsInScript()
{
	return currentScript != nullptr;
}

void UScriptManager::SetScriptExecuteSpeed(float newScriptExecuteSpeed)
{
	scriptExecuteSpeed = newScriptExecuteSpeed;
}

float UScriptManager::GetScriptExecuteSpeed()
{
	return scriptExecuteSpeed;
}

float UScriptManager::GetScriptTickTime()
{
	return scriptTickTime;
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
		FString chapterIndexName = var.Left(var.Len() - 4);
		chapter->SetChapterIndexName(chapterIndexName);
		mainChapterMap.Add(chapterIndexName, chapter);
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
	AddIegalAction(NewObject<UChangeControlActorAction>(this));
	AddIegalAction(NewObject<UMessageTipAction>(this));
	AddIegalAction(NewObject<UPlayBGMAction>(this)); 
	AddIegalAction(NewObject<UAddItemAction>(this));
	AddIegalAction(NewObject<UAddActorAction>(this));
	AddIegalAction(NewObject<URemoveMoneyAction>(this));
	AddIegalAction(NewObject<UOptionAction>(this));

	AddIegalAction(NewObject<URemoveActorAction>(this));
	AddIegalAction(NewObject<USetActorInfoAction>(this));
	AddIegalAction(NewObject<UAddCanControlActorAction>(this));
	AddIegalAction(NewObject<URemoveCanControlActorAction>(this));
	AddIegalAction(NewObject<UAddNextScriptAction>(this));
	AddIegalAction(NewObject<USetCanControlAction>(this));
	AddIegalAction(NewObject<USetTimeAction>(this));
	AddIegalAction(NewObject<USetRainAction>(this));
	AddIegalAction(NewObject<USetCloudyAction>(this)); 
	AddIegalAction(NewObject<UAddScriptVolumeAction>(this));
	AddIegalAction(NewObject<UConditionAction>(this));
	AddIegalAction(NewObject<UGetItemNumberAction>(this));
	AddIegalAction(NewObject<UGetMoneyAction>(this));
	AddIegalAction(NewObject<USetScriptActorAction>(this)); 
	AddIegalAction(NewObject<USetCanControlMoveAction>(this));
	AddIegalAction(NewObject<USetCanControlViewAction>(this));
	AddIegalAction(NewObject<USetScriptExecuteSpeedAction>(this));
	AddIegalAction(NewObject<URemoveScriptVolumeAction>(this));
	AddIegalAction(NewObject<UClearScriptActorAction>(this));
	AddIegalAction(NewObject<USetChapterStateAction>(this)); 
	AddIegalAction(NewObject<USetSectionStateAction>(this)); 
	AddIegalAction(NewObject<USetParagraphStateAction>(this));
	AddIegalAction(NewObject<USetMainUIStateAction>(this));
	AddIegalAction(NewObject<UStopScriptAction>(this));
	AddIegalAction(NewObject<URemoveNextScriptAction>(this));
}

void UScriptManager::AddIegalAction(UActionBase* actionBase)
{
	legalActionMap.Add(actionBase->GetActionName(), actionBase);
}

void UScriptManager::ScriptFinish()
{
	if (currentScript != nullptr)
	{
		currentScript = nullptr;
	}
	else
	{
		LogError(TEXT("UScriptManager::ScriptFinish currentScript为空。"));
	}
}

UActionBase* UScriptManager::GetIegalActionByName(FString actionName)
{
	if (legalActionMap.Contains(actionName))
	{
		return legalActionMap[actionName];
	}
	return nullptr;
}

FString UScriptManager::ExecuteAction(FString actionValue)
{
	if (! actionValue.IsEmpty())
	{
		TArray<FString> stringArray;
		actionValue.ParseIntoArray(stringArray, TEXT(" "));
		if (stringArray.Num() > 0)
		{
			UActionBase* actionBase = GetIegalActionByName(stringArray[0]);
			if (actionBase != nullptr)
			{
				UActionBase* actionBase2 = NewObject<UActionBase>(this, actionBase->GetClass());
				actionBase2->Load(stringArray);
				return actionBase2->Execute();
			}
			else
			{
				LogError(stringArray[0] + TEXT("指令不合法！"));
			}
		}
	}
	else
	{
		LogWarning(TEXT("指令为空，无法执行！"));
	}
	return FString();
}