#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Config/RecorderBase.h"
#include "ConfigManager.generated.h"

UCLASS()
class LEAVETHEPAST_API UConfigManager : public UObject
{
	GENERATED_BODY()
public:
	~UConfigManager();

	//获得指定名称的配置表
	UFUNCTION(BlueprintCallable)
	TMap<int, URecorderBase*> GetConfigByName(UClass* recorderClass);

	//获得指定名称和Id的配置
	UFUNCTION(BlueprintCallable)
	URecorderBase* GetConfigByNameId(UClass* recorderClass,int id);

	//加载指定名称的配置
	UFUNCTION(BlueprintCallable)
	void LoadConfigByName(UClass* recorderClass);

private:
	TMap<FString, TMap<int, URecorderBase*>*> configMap;

	FString configRootPath = TEXT("GameContent/Artres/Config/Recorder/");
};
