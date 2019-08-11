#include "CommonBlueprintFunctionLibrary.h"
#include "Engine/World.h"
#include "../LeaveThePastGameModeBase.h"
#include "../Manager/MainGameManager.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/ActorManager.h"
#include "../Manager/ConfigManager.h"
#include "../Manager/LogManager.h"
#include "../Manager/UIManager.h"
#include "../Manager/HelpManager.h"
#include "../Actor/DirectorActor.h"
#include "../Actor/ActorBase.h"
#include "Kismet/GameplayStatics.h"

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
	return ALeaveThePastGameModeBase::GetInstance();
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

UActorManager* UCommonBlueprintFunctionLibrary::GetActorManager()
{
	return UActorManager::GetInstance();
}

UUIManager* UCommonBlueprintFunctionLibrary::GetUIManager()
{
	return UUIManager::GetInstance();
}

AActorBase* UCommonBlueprintFunctionLibrary::GetCurrentControlActor()
{
	return ADirectorActor::GetInstance()->GetCurrentControlActor();
}

UTexture2D* UCommonBlueprintFunctionLibrary::LoadTexture2D(FString path, bool& isValid, int32& outWidth, int32& outHeight)
{
	return UHelpManager::LoadTexture2D(path, isValid, outWidth,outHeight);
}
