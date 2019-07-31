#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../Config/TimeData.h"
#include "MainGameManager.generated.h"

class UWorld;
class USystemData;
class UUserData;
class UDebugData;

class ADirectorActor;

class UConfigManager;
class UScriptManager;
class UActorManager;
class ULogManager;
class UUIManager;
class UAudioManager;

//管理游戏
UCLASS()
class LEAVETHEPAST_API UMainGameManager : public UGameInstance
{
	GENERATED_BODY()
public:
	static UMainGameManager* GetInstance();

	//初始化所有内容
	UFUNCTION(BlueprintCallable)
	void InitAll();

	//重新加载系统数据
	UFUNCTION(BlueprintCallable)
	void ReloadSystemData();

	//重新加载用户数据
	UFUNCTION(BlueprintCallable)
	void ReloadUserData();

	//重新加载调试数据
	UFUNCTION(BlueprintCallable)
	void ReloadDebugData();

	//开始计时
	UFUNCTION(BlueprintCallable)
	void StartTime();

	//停止计时
	UFUNCTION(BlueprintCallable)
	void StopTime();

	//是否计时
	UFUNCTION(BlueprintCallable)
	bool IsStartTime();

	//获得游戏运行的时间
	UFUNCTION(BlueprintCallable)
	FTimeData GetRealTimeData();

	//获得游戏运行的时间
	UFUNCTION(BlueprintCallable)
	FTimeData GetGameTimeData();

	//每帧执行一次
	UFUNCTION(BlueprintCallable)
	void Tick(float secondTime);

	//保存系统数据
	UFUNCTION(BlueprintCallable)
	void SaveSystemData();

	//获得系统数据
	UFUNCTION(BlueprintCallable)
	USystemData* GetSystemData();

	//保存用户数据
	UFUNCTION(BlueprintCallable)
	void SaveUserData();

	//获得用户数据
	UFUNCTION(BlueprintCallable)
	UUserData* GetUserData();

	//保存调试数据
	UFUNCTION(BlueprintCallable)
	void SaveDebugData();

	//获得调试数据
	UFUNCTION(BlueprintCallable)
	UDebugData* GetDebugData();

	//结束游戏
	UFUNCTION(BlueprintCallable)
	void ExitGame();

	//获得配置管理器
	UFUNCTION(BlueprintCallable)
	UConfigManager* GetConfigManager();

	//获得剧本管理器
	UFUNCTION(BlueprintCallable)
	UScriptManager* GetScriptManager();

	//获得角色管理器
	UFUNCTION(BlueprintCallable)
	UActorManager* GetActorManager();

	//获得角色管理器
	UFUNCTION(BlueprintCallable)
	ULogManager* GetLogManager();

	//获得UI管理器
	UFUNCTION(BlueprintCallable)
	UUIManager* GetUIManager();

	//获得声音管理器
	UFUNCTION(BlueprintCallable)
	UAudioManager* GetAudioManager();

	//获得资源路径
	UFUNCTION(BlueprintCallable)
	FString GetArtresPath();

	//使用物品
	UFUNCTION(BlueprintCallable)
	void UseItem(int itemId);

	//进入场景
	UFUNCTION(BlueprintCallable)
	void EnterScene(int sceneId);

	//获得游戏世界
	UFUNCTION(BlueprintCallable)
	UWorld* GetGameWorld();
private:
	//初始化管理类
	void InitManager();

	static UMainGameManager* gameManager;

	UPROPERTY()
	ADirectorActor* directorActor = nullptr;

	UPROPERTY()
	USystemData* systemData = nullptr;

	UPROPERTY()
	UUserData* userData = nullptr;

	UPROPERTY()
	UDebugData* debugData = nullptr;

	UPROPERTY()
	UConfigManager* configManager = nullptr;

	UPROPERTY()
	UScriptManager* scriptManager = nullptr;

	UPROPERTY()
	UActorManager* actorManager = nullptr;

	UPROPERTY()
	ULogManager* logManager = nullptr;

	UPROPERTY()
	UUIManager* uiManager = nullptr;

	UPROPERTY()
	UAudioManager* audioManager = nullptr;

	UPROPERTY()
	UWorld* gameWorld = nullptr;
	
	//是否已经初始化完成
	bool haveInited = false;
	bool startTime = false;

	FTimeData realTimeData;
};
