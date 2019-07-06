#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DramaScriptManager.generated.h"

class UActionBase;
class UChapter;

UCLASS()
class LEAVETHEPAST_API UDramaScriptManager : public UObject
{
	GENERATED_BODY()
public:
	static UDramaScriptManager* GetInstance();

	void Init();

	//开始执行任务
	UFUNCTION(BlueprintCallable)
	void StartDramaScriptMainByNameIndex(FString scriptName, int index);

	UFUNCTION(BlueprintCallable)
	void Tick();

	//加载所有剧本
	void LoadDramaScriptAll();
private:
	//加载主线剧本
	void LoadDramaScriptMain();

	static UDramaScriptManager* dramaScriptManager;

	FString dramaScriptMainRelativePath = TEXT("GameContent/Artres/DramaScript/Main/");
	TMap<FString, UChapter*> chapterMainMap;
	UChapter* currentScript = nullptr;
};
