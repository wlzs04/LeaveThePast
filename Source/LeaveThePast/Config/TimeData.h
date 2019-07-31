#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TimeData.generated.h"

//用来保存时间相关信息的结构体
USTRUCT(BlueprintType)
struct LEAVETHEPAST_API FTimeData
{
	GENERATED_USTRUCT_BODY()
public:
	void Tick(float secondTime);

	//获得小时
	float GetHours();
	float GetAllHours();

	//获得分钟
	float GetMinutes();
	float GetAllMinutes();

	//获得秒
	float GetSeconds();
	float GetAllSeconds();

	//获得毫秒
	float GetMilliseconds();
	float GetAllMilliseconds();

	//设置游戏时间，
	void SetTime(int hour, int minute, int second);

	//获得游戏时间，
	FTimespan GetTimespan();

private:
	float gameDuringSecond = 0;
};
