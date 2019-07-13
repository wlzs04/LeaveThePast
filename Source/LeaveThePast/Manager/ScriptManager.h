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
	void StartMainScriptByNameIndex(FString scriptName, int index);

	UFUNCTION(BlueprintCallable)
	void Tick();

	//加载所有剧本
	void LoadAllScript();

	UFUNCTION(BlueprintCallable)
	TMap<FString, UChapter*> GetMainChapterMap();
	UFUNCTION(BlueprintCallable)
	TMap<FString, UChapter*> GetSideChapterMap();
	UFUNCTION(BlueprintCallable)
	TMap<FString, UChapter*> GetSceneChapterMap();
private:
	//加载主线剧本
	void LoadMainScript();
	//加载支线剧本
	void LoadSideScript();
	//加载场景剧本
	void LoadSceneScript();

	static UScriptManager* scriptManager;

	FString mainScriptRelativePath = TEXT("GameContent/Artres/Script/Main/");
	FString sideScriptRelativePath = TEXT("GameContent/Artres/Script/Side/");
	FString sceneScriptRelativePath = TEXT("GameContent/Artres/Script/Scene/");

	TMap<FString, UChapter*> mainChapterMap;
	TMap<FString, UChapter*> sideChapterMap;
	TMap<FString, UChapter*> sceneChapterMap;

	UChapter* currentScript = nullptr;
};
