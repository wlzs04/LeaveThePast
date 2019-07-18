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

	void SetActorId(int newActorId)
	{
		actorId = newActorId;
	}

	void SetPosition(FVector newPosition)
	{
		position = newPosition;
	}

	void SetRotation(FRotator newRotation)
	{
		rotation = newRotation;
	}

	int actorId;
	FVector position;
	FRotator rotation;
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
	UTimeData* GetGameTimeData();

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

protected:
	//保存路径
	FString savePath;

	UPROPERTY()
	UTimeData* gameTimeData = nullptr;

	bool isFixedTime = false;//是否固定时间
	float gameAndRealTimeRate = 1;
	int sceneId = 10001;//角色所在场景Id
	TArray<FSaveActorInfo> canControlActorList;//可控演员列表
	TMap<int, int> itemMap;
};
