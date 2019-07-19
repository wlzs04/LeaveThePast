#include "CommonBlueprintFunctionLibrary.h"
#include "Engine/World.h"

int UCommonBlueprintFunctionLibrary::GetHours(FTimeData time)
{
	return time.GetHours();
}

int UCommonBlueprintFunctionLibrary::GetMinutes(FTimeData time)
{
	return time.GetMinutes();
}

int UCommonBlueprintFunctionLibrary::GetSeconds(FTimeData time)
{
	return time.GetSeconds();
}

ALeaveThePastGameModeBase* UCommonBlueprintFunctionLibrary::GetMainGameMode()
{
	return GWorld->GetAuthGameMode<ALeaveThePastGameModeBase>();
}

UMainGameManager* UCommonBlueprintFunctionLibrary::GetMainGameManager()
{
	return UMainGameManager::GetInstance();
}

UConfigManager* UCommonBlueprintFunctionLibrary::GetConfigGameManager()
{
	return UConfigManager::GetInstance();
}

UScriptManager* UCommonBlueprintFunctionLibrary::GetScriptManager()
{
	return UScriptManager::GetInstance();
}
