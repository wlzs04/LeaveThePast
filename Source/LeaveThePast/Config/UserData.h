#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserData.generated.h"

class UGameManager;

UCLASS()
class LEAVETHEPAST_API UUserData : public UObject
{
	GENERATED_BODY()
public:
	UUserData();

	void Load();

	void Save();

	int GetHour();

	int GetMinute();

	int GetSecond();

	bool GetIsFixedTime();

	float GetGameAndRealTimeRate();

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

	int hour = 6;//时
	int minute = 0;//分
	int second = 0;//秒
	bool isFixedTime = false;//是否固定时间
	float gameAndRealTimeRate = 1;
	TMap<int, int> itemMap;
};
