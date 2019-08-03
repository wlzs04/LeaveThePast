#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Config/ScriptItemData.h"
#include "ScriptManager.generated.h"

class UActionBase;
class UParagraph;

//管理剧情及执行指令
UCLASS()
class LEAVETHEPAST_API UScriptManager : public UObject
{
	GENERATED_BODY()
public:
	static UScriptManager* GetInstance();

	void Init();

	//开始执行任务
	UFUNCTION(BlueprintCallable)
	void StartScript(FString chapterName, int sectionId,int paragrapgId);

	//开始执行需要运行的脚本
	UFUNCTION(BlueprintCallable)
	void StartNextScript();

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
	FString ExecuteActionString(FString actionValue);

	//执行指令段
	UFUNCTION(BlueprintCallable)
	void ExecuteParagraph(UParagraph* newParagraph);

	//加载所有剧本
	void LoadAllScript();

	UFUNCTION(BlueprintCallable)
	TMap<FString, UChapter*> GetMainChapterMap();
	UFUNCTION(BlueprintCallable)
	TMap<FString, UChapter*> GetSideChapterMap();
	UFUNCTION(BlueprintCallable)
	TMap<FString, UChapter*> GetSceneChapterMap();

	//跳过当前执行章节,如果中间有不可跳过的，无法跳过，跳过后当前剧本设置为完成
	UFUNCTION(BlueprintCallable)
	void SkipScript();

	//判断是否在剧本执行中
	UFUNCTION(BlueprintCallable)
	bool IsExecutingScript();

	//获得当前剧本信息
	UFUNCTION(BlueprintCallable)
	FScriptItemData GetCurrentScriptItemData();

	//设置剧本执行速度
	UFUNCTION(BlueprintCallable)
	void SetScriptExecuteSpeed(float newScriptExecuteSpeed);

	//获得剧本执行速度
	UFUNCTION(BlueprintCallable)
	float GetScriptExecuteSpeed();

	//获得剧本一帧的时间
	UFUNCTION(BlueprintCallable)
	float GetScriptTickTime();
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

	UPROPERTY()
	TMap<FString, UActionBase*> legalActionMap;

	FString mainScriptRelativePath = TEXT("GameContent/Artres/Script/Main/");
	FString sideScriptRelativePath = TEXT("GameContent/Artres/Script/Side/");
	FString sceneScriptRelativePath = TEXT("GameContent/Artres/Script/Scene/");

	UPROPERTY()
	TMap<FString, UChapter*> mainChapterMap;
	UPROPERTY()
	TMap<FString, UChapter*> sideChapterMap;
	UPROPERTY()
	TMap<FString, UChapter*> sceneChapterMap;

	UPROPERTY()
	UParagraph* currentParagraph = nullptr;
	bool isExecutingScript = false;//是否正在执行剧本
	FScriptItemData currentScriptItemData;

	float scriptExecuteSpeed = 1;//剧本执行速度
	float scriptTickTime = 0;
};
