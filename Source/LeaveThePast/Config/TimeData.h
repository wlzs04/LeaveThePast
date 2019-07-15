#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TimeData.generated.h"

/**
 * 用来保存时间相关信息的类
 */
UCLASS(BlueprintType)
class LEAVETHEPAST_API UTimeData : public UObject
{
	GENERATED_BODY()
public:
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
	float gameDuringSecond = 0;
};
