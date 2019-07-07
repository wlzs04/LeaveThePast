#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LogManager.generated.h"

//日志等级
UENUM(BlueprintType)
enum class LogLevelEnum :uint8
{
	Normal,//普通
	Warning,//警告
	Error,//错误
};

UCLASS()
class LEAVETHEPAST_API ULogManager : public UObject
{
	GENERATED_BODY()
public:
	static ULogManager* GetInstance();

	void Init();

	void SetEnable(bool newEnableLogToFile, bool newEnableLogToEdit);

	void LogContent(LogLevelEnum logLevel, FString content, FString logFile, FString logFunction, int logLine, FString logDate, FString logTime);
	void LogContent(LogLevelEnum logLevel, FString content);

private:
	void LogContentReal(LogLevelEnum logLevel,FString realContent);

	FString filePath;
	bool enableLogToFile = true;
	bool enableLogToEdit = true;

	static ULogManager* logManager;
};

#define LogNormal(x) ULogManager::GetInstance()->LogContent(LogLevelEnum::Normal, x);
#define LogWarning(x) ULogManager::GetInstance()->LogContent(LogLevelEnum::Warning, x);
#define LogError(x) ULogManager::GetInstance()->LogContent(LogLevelEnum::Error, x);

#define LogNormalDetail(x) ULogManager::GetInstance()->LogContent(LogLevelEnum::Normal, x, TEXT(__FILE__),TEXT(__FUNCTION__), __LINE__, TEXT(__DATE__), TEXT(__TIME__));
#define LogWarningDetail(x) ULogManager::GetInstance()->LogContent(LogLevelEnum::Warning, x, TEXT(__FILE__),TEXT(__FUNCTION__), __LINE__, TEXT(__DATE__), TEXT(__TIME__));
#define LogErrorDetail(x) ULogManager::GetInstance()->LogContent(LogLevelEnum::Error, x, TEXT(__FILE__),TEXT(__FUNCTION__), __LINE__, TEXT(__DATE__), TEXT(__TIME__));