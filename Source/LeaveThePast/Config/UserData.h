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
