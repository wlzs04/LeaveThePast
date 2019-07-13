#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ConfigManager.h"
#include "ScriptManager.h"
#include "ActorManager.h"
#include "LogManager.h"
#include "UIManager.h"
#include "AudioManager.h"
#include "../Config/UserData.h"
#include "../Config/SystemData.h"
#include "MainGameManager.generated.h"

/**
 * 用来保存时间相关信息的类
 */
UCLASS(BlueprintType)
class LEAVETHEPAST_API UTimeData : public UObject
{
	GENERATED_BODY()
public:
	UTimeData();
	~UTimeData();

	void Tick(float secondTime);

	//获得小时
	UFUNCTION(BlueprintCallable)
	float GetHours();
	UFUNCTION(BlueprintCallable)
	float GetAllHours();

	//获得分钟
	UFUNCTION(BlueprintCallable)
	float GetMinutes();
	UFUNCTION(BlueprintCallable)
	float GetAllMinutes();

	//获得秒
	UFUNCTION(BlueprintCallable)
	float GetSeconds();
	UFUNCTION(BlueprintCallable)
	float GetAllSeconds();

	//获得毫秒
	UFUNCTION(BlueprintCallable)
	float GetMilliseconds();
	UFUNCTION(BlueprintCallable)
	float GetAllMilliseconds();

	//设置游戏时间，
	UFUNCTION(BlueprintCallable)
	void SetTime(int hour, int minute, int second);
private:
	float gameDuringSecond;
};

UCLASS()
class LEAVETHEPAST_API UMainGameManager : public UGameInstance
{
	GENERATED_BODY()
public:
	static UMainGameManager* GetInstance();

	//初始化所有内容
	UFUNCTION(BlueprintCallable)
	void InitAll();

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

	//设置游戏和现实时间的比率
	UFUNCTION(BlueprintCallable)
	void SetGameAndRealTimeRate(float newGameAndRealTimeRate);

	//设置游戏和现实时间的比率
	UFUNCTION(BlueprintCallable)
	float GetGameAndRealTimeRate();

	//每帧执行一次
	UFUNCTION(BlueprintCallable)
	void Tick(float secondTime);

	//加载系统数据
	UFUNCTION(BlueprintCallable)
	void LoadSystemData();

	//保存系统数据
	UFUNCTION(BlueprintCallable)
	void SaveSystemData();

	//获得系统数据
	UFUNCTION(BlueprintCallable)
	USystemData* GetSystemData();

	//加载用户数据
	UFUNCTION(BlueprintCallable)
	void LoadUserData();

	//保存用户数据
	UFUNCTION(BlueprintCallable)
	void SaveUserData();

	//获得用户数据
	UFUNCTION(BlueprintCallable)
	UUserData* GetUserData();

	//设置是否固定时间
	UFUNCTION(BlueprintCallable)
	void SetIsFixedTime(bool newIsFixedTime);

	//获得是否固定时间
	UFUNCTION(BlueprintCallable)
	bool GetIsFixedTime();

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

	//加载合法指令
	void AddIegalAction(UActionBase* actionBase);

	//通过指令名称获得指令
	UFUNCTION(BlueprintCallable)
	UActionBase* GetIegalActionByName(FString actionName);

	//执行指令
	UFUNCTION(BlueprintCallable)
	void ExecuteAction(FString actionValue);

	//使用物品
	UFUNCTION(BlueprintCallable)
	void UseItem(int itemId);
private:
	//初始化管理类
	void InitManager();

	//加载合法指令
	void LoadIegalAction();

	//初始化游戏时间
	void InitGameTime();

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
	float gameAndRealTimeRate = 1;
	bool isFixedTime = false;//是否固定时间

	UPROPERTY()
	UTimeData* realTimeData = nullptr;

	UPROPERTY()
	UTimeData* gameTimeData = nullptr;

	TMap<FString, UActionBase*> legalActionMap;

	AActorBase* mainActor = nullptr;
	AActorBase* mainActor2 = nullptr;
	AActorBase* cameraActor = nullptr;
};
