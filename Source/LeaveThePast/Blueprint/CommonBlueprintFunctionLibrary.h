#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../Config/TimeData.h"
#include "../Manager/MainGameManager.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/ConfigManager.h"
#include "../Manager/LogManager.h"
#include "../LeaveThePastGameModeBase.h"
#include "CommonBlueprintFunctionLibrary.generated.h"

UCLASS()
class LEAVETHEPAST_API UCommonBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//获得小时
	UFUNCTION(BlueprintCallable,Category="Main|FTimeData")
	static int GetHours(FTimeData time);

	//获得分钟
	UFUNCTION(BlueprintCallable, Category = "Main|FTimeData")
	static int GetMinutes(FTimeData time);

	//获得秒
	UFUNCTION(BlueprintCallable, Category = "Main|FTimeData")
	static int GetSeconds(FTimeData time);

	//获得MainGameMode
	UFUNCTION(BlueprintCallable, Category = "Main|Manager")
	static ALeaveThePastGameModeBase* GetMainGameMode();

	//获得MainGameManager
	UFUNCTION(BlueprintCallable, Category = "Main|Manager")
	static UMainGameManager* GetMainGameManager();

	//获得MainGameManager
	UFUNCTION(BlueprintCallable, Category = "Main|Manager")
	static UConfigManager* GetConfigManager();

	//获得MainGameManager
	UFUNCTION(BlueprintCallable, Category = "Main|Manager")
	static UScriptManager* GetScriptManager();

	//加载本地图片
	UFUNCTION(BlueprintCallable, Category = "Main|Texture")
	static UTexture2D* LoadTexture2D(FString path, bool& isValid, int32& outWidth, int32& outHeight);
};
