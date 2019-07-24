#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScriptManager.generated.h"

class UActionBase;
class UChapter;

UCLASS()
class LEAVETHEPAST_API UScriptManager : public UObject
{
	GENERATED_BODY()
public:
	static UScriptManager* GetInstance();

	void Init();

	//开始执行任务
	UFUNCTION(BlueprintCallable)
	void StartMainScriptByNameIndex(FString scriptName, int sectionId,int paragrapgId);

	//停止当前剧本，不算完成，一般用于玩家手动停止和某些条件不符被动停止
	UFUNCTION(BlueprintCallable)
	void StopCurrentScript();

	UFUNCTION(BlueprintCallable)
	void Tick();

	//通过指令名称获得指令
	UFUNCTION(BlueprintCallable)
	UActionBase* GetIegalActionByName(FString actionName);

	//执行指令
	UFUNCTION(BlueprintCallable)
	FString ExecuteAction(FString actionValue);

	//加载所有剧本
	void LoadAllScript();

	UFUNCTION(BlueprintCallable)
	TMap<FString, UChapter*> GetMainChapterMap();
	UFUNCTION(BlueprintCallable)
	TMap<FString, UChapter*> GetSideChapterMap();
	UFUNCTION(BlueprintCallable)
	TMap<FString, UChapter*> GetSceneChapterMap();

	//执行指令
	UFUNCTION(BlueprintCallable)
	UChapter* GetCurrentChapter();

private:
	//加载主线剧本
	void LoadMainScript();
	//加载支线剧本
	void LoadSideScript();
	//加载场景剧本
	void LoadSceneScript();

	//加载所有合法指令
	void LoadAllIegalAction();
	//加载合法指令
	void AddIegalAction(UActionBase* actionBase);

	//剧本结束
	void ScriptFinish();

	static UScriptManager* scriptManager;

	TMap<FString, UActionBase*> legalActionMap;

	FString mainScriptRelativePath = TEXT("GameContent/Artres/Script/Main/");
	FString sideScriptRelativePath = TEXT("GameContent/Artres/Script/Side/");
	FString sceneScriptRelativePath = TEXT("GameContent/Artres/Script/Scene/");

	TMap<FString, UChapter*> mainChapterMap;
	TMap<FString, UChapter*> sideChapterMap;
	TMap<FString, UChapter*> sceneChapterMap;

	UChapter* currentScript = nullptr;
};
