#include "TimeData.h"

void UTimeData::Tick(float secondTime)
{
	gameDuringSecond += secondTime;
}

float UTimeData::GetHours()
{
	return (int)GetAllHours() % 24;
}

float UTimeData::GetAllHours()
{
	return gameDuringSecond / 3600;
}

float UTimeData::GetMinutes()
{
	return (int)GetAllMinutes() % 60;
}

float UTimeData::GetAllMinutes()
{
	return gameDuringSecond / 60;
}

float UTimeData::GetSeconds()
{
	return ((int)gameDuringSecond) % 60;
}

float UTimeData::GetAllSeconds()
{
	return gameDuringSecond;
}

float UTimeData::GetMilliseconds()
{
	return (gameDuringSecond - (int)gameDuringSecond) * 1000;
}

float UTimeData::GetAllMilliseconds()
{
	return gameDuringSecond * 1000;
}

void UTimeData::SetTime(int hour, int minute, int second)
{
	second = FMath::Clamp(second, 0, 59);
	gameDuringSecond = second;
	minute = FMath::Clamp(minute, 0, 59);
	gameDuringSecond += minute * 60;
	hour = FMath::Max(0, hour);
	gameDuringSecond += hour * 3600;
}

FTimespan UTimeData::GetTimespan()
{
	return FTimespan(GetHours(),GetMinutes(),GetSeconds());
}
