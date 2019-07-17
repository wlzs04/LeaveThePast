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
