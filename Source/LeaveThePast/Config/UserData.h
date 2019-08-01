#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TimeData.h"
#include "ScriptItemData.h"
#include "UserData.generated.h"

class FXmlNode;
class UChapterData;
class USceneActorData;
class USceneVolumeData;

//玩家数据
UCLASS(BlueprintType)
class LEAVETHEPAST_API UUserData : public UObject
{
	GENERATED_BODY()
public:
	UUserData();

	void Load();

	void Save();

	//设置初始存档
	void SetInitData();

	UFUNCTION(BlueprintCallable)
	FTimeData GetGameTimeData();

	//设置游戏内时间
	UFUNCTION(BlueprintCallable)
	void SetGameTime(int hour, int minute, int second);

	void Tick(float secondTime);

	UFUNCTION(BlueprintCallable)
	void SetIsFixedTime(bool newIsFixedTime);
	UFUNCTION(BlueprintCallable)
	bool GetIsFixedTime();

	UFUNCTION(BlueprintCallable)
	void SetGameAndRealTimeRate(float newGameAndRealTimeRate);
	UFUNCTION(BlueprintCallable)
	float GetGameAndRealTimeRate();

	//场景
	UFUNCTION(BlueprintCallable)
	void SetSceneId(int newSceneId);
	UFUNCTION(BlueprintCallable)
	int GetSceneId();

	//获得当前控制第几个演员
	int GetCurrentControlActorIndex();

	//可控演员列表
	TArray<int> GetCanControlActorList();

	//添加可控演员
	void AddControlActor(int actorInfoId);

	//移除可控演员
	void RemoveControlActor(int actorInfoId);

	//场景演员列表
	TArray<USceneActorData*> GetSceneActorList();

	//场景体积列表
	TArray<USceneVolumeData*> GetSceneVolumeList();
	
	//获得物品map
	UFUNCTION(BlueprintCallable)
	TMap<int, int> GetItemMap();

	//获得物品数量
	UFUNCTION(BlueprintCallable)
	int GetItemNumberById(int itemId);

	//添加物品
	UFUNCTION(BlueprintCallable)
	void AddItem(int itemId,int number);

	//减少物品，返回实际减少的个数
	UFUNCTION(BlueprintCallable)
	int ReduceItem(int itemId, int number);

	//设置物品数量
	UFUNCTION(BlueprintCallable)
	void SetItemNumber(int itemId, int number);

	//获得钱数 根据物品中铜钱、银两等值钱物品进行换算
	UFUNCTION(BlueprintCallable)
	int GetMoney();

	//消耗钱
	UFUNCTION(BlueprintCallable)
	void ReduceMoney(int money);

	//获得剧本Map
	UFUNCTION(BlueprintCallable)
	TMap<FString, UChapterData*> GetChapterMap();

	void SetChapterState(FString scriptName, int state);
	void SetSectionState(FString scriptName, int sectionId, int state);
	void SetParagraphState(FString scriptName, int sectionId, int paragrapgId, int state);

	//获得玩家即将运行的剧本列表
	UFUNCTION(BlueprintCallable)
	TArray<FScriptItemData> GetNextScriptList();

	//添加玩家即将运行的剧本
	UFUNCTION(BlueprintCallable)
	void AddNextScript(FScriptItemData newScriptItemData);

	//移除玩家即将运行的剧本
	UFUNCTION(BlueprintCallable)
	void RemoveNextScript(FScriptItemData newScriptItemData);
protected:
	//保存路径
	FString savePath;

	FTimeData gameTimeData;

	bool isFixedTime = false;//是否固定时间
	float gameAndRealTimeRate = 1;
	int sceneId = 10001;//角色所在场景Id

	int currentControlActorIndex = 0;//当前控制第几个
	TArray<int> canControlActorList;//可控演员列表

	UPROPERTY()
	TArray<USceneActorData*> sceneActorList;//场景演员列表
	UPROPERTY()
	TArray<USceneVolumeData*> sceneVolumeList;//场景体积列表
	
	TMap<int, int> itemMap;

	UPROPERTY()
	TMap<FString, UChapterData*> chapterMap;//剧本状态

	TArray<FScriptItemData> nextScriptList;//玩家即将运行的剧本列表，在游戏开始后立即执行
};
