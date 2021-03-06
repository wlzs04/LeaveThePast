#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../Config/TimeData.h"
#include "CommonBlueprintFunctionLibrary.generated.h"

class ALeaveThePastGameModeBase;
class UMainGameManager;
class UConfigManager;
class UScriptManager;
class UActorManager;
class UUIManager;
class UTexture2D;
class AActorBase;

//常用函数
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

	//获得ConfigManager
	UFUNCTION(BlueprintCallable, Category = "Main|Manager")
	static UConfigManager* GetConfigManager();

	//获得ScriptManager
	UFUNCTION(BlueprintCallable, Category = "Main|Manager")
	static UScriptManager* GetScriptManager();

	//获得ScriptManager
	UFUNCTION(BlueprintCallable, Category = "Main|Manager")
	static UActorManager* GetActorManager();

	//获得MainGameManager
	UFUNCTION(BlueprintCallable, Category = "Main|Manager")
	static UUIManager* GetUIManager();

	//获得当前玩家控制角色
	UFUNCTION(BlueprintCallable, Category = "Main|Manager")
	static AActorBase* GetCurrentControlActor();

	//加载本地图片
	UFUNCTION(BlueprintCallable, Category = "Main|Texture")
	static UTexture2D* LoadTexture2D(FString path, bool& isValid, int32& outWidth, int32& outHeight);
};
