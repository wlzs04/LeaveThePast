#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TimeData.h"
#include "UserData.generated.h"

USTRUCT(BlueprintType)
struct FSaveActorInfo
{
	GENERATED_USTRUCT_BODY()

	FSaveActorInfo()
	{
		actorId = 0;
	}

	int actorId;
	FVector position;
	FRotator rotation;
};

USTRUCT(BlueprintType)
struct FSaveSectionInfo
{
	GENERATED_USTRUCT_BODY()

	FSaveSectionInfo()
	{
		id = 0;
		state = 0;
	}

	int id;
	int state;//0 未开始 1 进行中 2 完成 3 失败
	TMap<int, int> paragraphMap;
};

USTRUCT(BlueprintType)
struct FSaveChapterInfo
{
	GENERATED_USTRUCT_BODY()

	FSaveChapterInfo()
	{
		state = 0;
	}

	FString name;
	int state;//0 未开始 1 进行中 2 完成 3 失败
	TMap<int, FSaveSectionInfo> sectionMap;
};

UCLASS(BlueprintType)
class LEAVETHEPAST_API UUserData : public UObject
{
	GENERATED_BODY()
public:
	UUserData();

	void Load();

	void Save();

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

	//可控演员列表
	TArray<FSaveActorInfo> GetCanControlActorList();
	
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
	TMap<FString, FSaveChapterInfo> GetChapterMap();
protected:
	//保存路径
	FString savePath;

	FTimeData gameTimeData;

	bool isFixedTime = false;//是否固定时间
	float gameAndRealTimeRate = 1;
	int sceneId = 10001;//角色所在场景Id
	TArray<FSaveActorInfo> canControlActorList;//可控演员列表
	TMap<int, int> itemMap;

	TMap<FString, FSaveChapterInfo> chapterMap;//剧本
};
