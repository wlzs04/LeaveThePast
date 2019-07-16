#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ConfigManager.h"
#include "ScriptManager.h"
#include "ActorManager.h"
#include "LogManager.h"
#include "UIManager.h"
#include "AudioManager.h"
#include "../Config/TimeData.h"
#include "../Config/UserData.h"
#include "../Config/SystemData.h"
#include "MainGameManager.generated.h"

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
	UTimeData* GetRealDuringTime();

	//获得游戏运行的时间
	UFUNCTION(BlueprintCallable)
	UTimeData* GetGameDuringTime();

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

	//加载本地图片
	UFUNCTION(BlueprintCallable)
	UTexture2D* LoadTexture2D(FString path, bool& isValid, int32& outWidth, int32& outHeight);

	//使用物品
	UFUNCTION(BlueprintCallable)
	void UseItem(int itemId);
private:
	//初始化管理类
	void InitManager();

	static UMainGameManager* gameManager;

	UPROPERTY()
	USystemData* systemData = nullptr;

	UPROPERTY()
	UUserData* userData = nullptr;

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
	
	//是否已经初始化完成
	bool haveInited = false;
	bool startTime = false;

	UPROPERTY()
	UTimeData* realTimeData = nullptr;

	UPROPERTY()
	UTimeData* gameTimeData = nullptr;

	AActorBase* mainActor = nullptr;
	AActorBase* mainActor2 = nullptr;
	AActorBase* cameraActor = nullptr;
};
