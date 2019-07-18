#include "HelpManager.h"

UHelpManager* UHelpManager::helpManager = nullptr;

void UHelpManager::Init()
{
	UHelpManager::helpManager = this;
}

FVector UHelpManager::ConvertFStringToFVector(FString value)
{
	TArray<FString> stringArray;
	value.ParseIntoArray(stringArray, TEXT(","));
	float x = 0;
	float y = 0;
	float z = 0;
	if (stringArray.Num() == 3)
	{
		x = FCString::Atof(*stringArray[0]);
		y = FCString::Atof(*stringArray[1]);
		z = FCString::Atof(*stringArray[2]);
	}
	return FVector(x,y,z);
}

FString UHelpManager::ConvertToFString(FVector value)
{
	return FString::FromInt(value.X) + TEXT(",")+ FString::FromInt(value.Y) + TEXT(",")+ FString::FromInt(value.Z);
}

FString UHelpManager::ConvertToFString(FRotator value)
{
	return FString::FromInt(value.Roll) + TEXT(",") + FString::FromInt(value.Pitch) + TEXT(",") + FString::FromInt(value.Yaw);
}

FString UHelpManager::ConvertToFString(FTimespan value)
{
	return FString::FromInt(value.GetHours()) + TEXT(":") + FString::FromInt(value.GetMinutes()) + TEXT(":") + FString::FromInt(value.GetSeconds());
}

FTimespan UHelpManager::ConvertFStringToFTimespan(FString value)
{
	TArray<FString> stringArray;
	value.ParseIntoArray(stringArray, TEXT(":"));
	float x = 0;
	float y = 0;
	float z = 0;
	if (stringArray.Num() == 3)
	{
		x = FCString::Atof(*stringArray[0]);
		y = FCString::Atof(*stringArray[1]);
		z = FCString::Atof(*stringArray[2]);
	}
	return FTimespan(x, y, z);
}

FRotator UHelpManager::ConvertFStringToFRotator(FString value)
{
	TArray<FString> stringArray;
	value.ParseIntoArray(stringArray, TEXT(","));
	float x = 0;
	float y = 0;
	float z = 0;
	if (stringArray.Num() == 3)
	{
		x = FCString::Atof(*stringArray[0]);
		y = FCString::Atof(*stringArray[1]);
		z = FCString::Atof(*stringArray[2]);
	}
	return FRotator(y, z, x);
}
