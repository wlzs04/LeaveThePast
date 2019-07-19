#include "TimeData.h"

void FTimeData::Tick(float secondTime)
{
	gameDuringSecond += secondTime;
}

float FTimeData::GetHours()
{
	return (int)GetAllHours() % 24;
}

float FTimeData::GetAllHours()
{
	return gameDuringSecond / 3600;
}

float FTimeData::GetMinutes()
{
	return (int)GetAllMinutes() % 60;
}

float FTimeData::GetAllMinutes()
{
	return gameDuringSecond / 60;
}

float FTimeData::GetSeconds()
{
	return ((int)gameDuringSecond) % 60;
}

float FTimeData::GetAllSeconds()
{
	return gameDuringSecond;
}

float FTimeData::GetMilliseconds()
{
	return (gameDuringSecond - (int)gameDuringSecond) * 1000;
}

float FTimeData::GetAllMilliseconds()
{
	return gameDuringSecond * 1000;
}

void FTimeData::SetTime(int hour, int minute, int second)
{
	second = FMath::Clamp(second, 0, 59);
	gameDuringSecond = second;
	minute = FMath::Clamp(minute, 0, 59);
	gameDuringSecond += minute * 60;
	hour = FMath::Max(0, hour);
	gameDuringSecond += hour * 3600;
}

FTimespan FTimeData::GetTimespan()
{
	return FTimespan(GetHours(),GetMinutes(),GetSeconds());
}
