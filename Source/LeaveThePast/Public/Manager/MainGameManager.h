#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ConfigManager.h"
#include "DramaScriptManager.h"
#include "ActorManager.h"
#include "../Config/UserData.h"
#include "../Config/SystemData.h"
#include "MainGameManager.generated.h"

UCLASS()
class LEAVETHEPAST_API UMainGameManager : public UGameInstance
{
	GENERATED_BODY()
public:
	//初始化所有内容
	UFUNCTION(BlueprintCallable)
	void InitAll();

	//游戏开始
	UFUNCTION(BlueprintCallable)
	void BeginGame();

	//开始计时
	UFUNCTION(BlueprintCallable)
	void StartTime();

	//停止计时
	UFUNCTION(BlueprintCallable)
	void StopTime();

	//是否计时
	UFUNCTION(BlueprintCallable)
	bool IsStartTime();

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

	//结束游戏
	UFUNCTION(BlueprintCallable)
	void ExitGame();

	//获得配置管理器
	UFUNCTION(BlueprintCallable)
	UConfigManager* GetConfigManager();

	//获得剧本管理器
	UFUNCTION(BlueprintCallable)
	UDramaScriptManager* GetDramaScriptManager();

	//获得剧本管理器
	UFUNCTION(BlueprintCallable)
	UActorManager* GetActorManager();

	//加载本地图片
	UFUNCTION(BlueprintCallable)
	UTexture2D* LoadTexture2D(FString path, bool& isValid, int32& outWidth, int32& outHeight);

	//加载合法指令
	void AddIegalAction(UActionBase* actionBase);

	//通过指令名称获得指令
	UFUNCTION(BlueprintCallable)
	UActionBase* GetIegalActionByName(FString actionName);

	//执行指令
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	//void ExecuteAction_BPEvent(const FString& actionString);
private:
	//初始化管理类
	void InitManager();

	//加载合法指令
	void LoadIegalAction();

	//初始化游戏时间
	void InitGameTime();

	UPROPERTY()
	USystemData* systemData = nullptr;

	UPROPERTY()
	UUserData* userData = nullptr;

	UPROPERTY()
	UConfigManager* configManager = nullptr;

	UPROPERTY()
	UDramaScriptManager* dramaScriptManager = nullptr;

	UPROPERTY()
	UActorManager* actorManager = nullptr;

	//是否已经初始化完成
	bool haveInited = false;
	bool startTime = false;
	float gameAndRealTimeRate = 1;
	bool isFixedTime = false;//是否固定时间

	TMap<FString, UActionBase*> legalActionMap;
};
