#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ConfigManager.generated.h"

class URecorderBase;

//管理配置
UCLASS()
class LEAVETHEPAST_API UConfigManager : public UObject
{
	GENERATED_BODY()
public:
	~UConfigManager();

	static UConfigManager* GetInstance();

	void Init();

	//获得指定名称的配置表
	UFUNCTION(BlueprintCallable)
	TMap<int, URecorderBase*> GetConfigByName(UClass* recorderClass,FString configName);

	//获得指定名称和Id的配置
	UFUNCTION(BlueprintCallable)
	URecorderBase* GetConfigByNameId(UClass* recorderClass, FString configName,int id);
private:
	//加载指定名称的配置
	void LoadConfigByName(UClass* recorderClass, FString configName);

	static UConfigManager* configManager;

	TMap<FString, TMap<int, URecorderBase*>*> configMap;

	FString configRootPath = TEXT("GameContent/Artres/Config/Recorder/");
};
