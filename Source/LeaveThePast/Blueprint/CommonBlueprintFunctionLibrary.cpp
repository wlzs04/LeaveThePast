#include "CommonBlueprintFunctionLibrary.h"
#include "Engine/World.h"
#include "../Manager/HelpManager.h"

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

UConfigManager* UCommonBlueprintFunctionLibrary::GetConfigManager()
{
	return UConfigManager::GetInstance();
}

UScriptManager* UCommonBlueprintFunctionLibrary::GetScriptManager()
{
	return UScriptManager::GetInstance();
}

UUIManager* UCommonBlueprintFunctionLibrary::GetUIManager()
{
	return UUIManager::GetInstance();
}

UTexture2D* UCommonBlueprintFunctionLibrary::LoadTexture2D(FString path, bool& isValid, int32& outWidth, int32& outHeight)
{
	return UHelpManager::LoadTexture2D(path, isValid, outWidth,outHeight);
}
