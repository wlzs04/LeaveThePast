#include "LogManager.h"
#include "MainGameManager.h"
#include "FileHelper.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "LogMacros.h"
#include <iostream>

ULogManager* ULogManager::logManager = nullptr;

ULogManager* ULogManager::GetInstance()
{
	return logManager;
}

void ULogManager::Init()
{
	filePath = UMainGameManager::GetInstance()->GetArtresPath()+TEXT("Log.log");
	FFileHelper::SaveStringToFile(TEXT(""), *filePath);
	ULogManager::logManager = this;
}

void ULogManager::SetEnable(bool newEnableLogToFile, bool newEnableLogToEdit)
{
	enableLogToFile = newEnableLogToFile;
	enableLogToEdit = newEnableLogToEdit;
}

void ULogManager::LogContent(LogLevelEnum logLevel, FString content, FString logFile, FString logFunction, int logLine, FString logDate, FString logTime)
{
	if ((!enableLogToFile && !enableLogToEdit) || filePath.IsEmpty())
	{
		return;
	}

	FString sentence;
	sentence.Append(TEXT(" File:"));
	sentence.Append(logFile);
	sentence.Append(TEXT(" Function:"));
	sentence.Append(logFunction);
	sentence.Append(TEXT(" Line:"));
	sentence.Append(FString::FromInt(logLine));
	sentence.Append(TEXT(" Time:"));
	sentence.Append(logDate + TEXT(" ") + logTime);
	sentence.Append(TEXT(" Content:"));
	sentence.Append(content);
	sentence.Append(TEXT("\n"));

	LogContentReal(logLevel,sentence);
}

void ULogManager::LogContent(LogLevelEnum logLevel, FString content)
{
	if ((!enableLogToFile && !enableLogToEdit) || filePath.IsEmpty())
	{
		return;
	}

	FString sentence;
	sentence.Append(TEXT(" Content:"));
	sentence.Append(content);
	sentence.Append(TEXT("\n"));

	LogContentReal(logLevel, sentence);
}

void ULogManager::LogContentReal(LogLevelEnum logLevel, FString realContent)
{
	if (enableLogToFile)
	{
		FString sentence;
		switch (logLevel)
		{
		case LogLevelEnum::Normal:
			sentence.Append(TEXT("Normal:"));
			break;
		case LogLevelEnum::Warning:
			sentence.Append(TEXT("Warning:"));
			break;
		case LogLevelEnum::Error:
			sentence.Append(TEXT("Error:"));
			break;
		default:
			break;
		}
		sentence.Append(realContent);
		FFileHelper::SaveStringToFile(sentence, *filePath, FFileHelper::EEncodingOptions::ForceUTF8, &IFileManager::Get(), FILEWRITE_Append);
	}
	if (enableLogToEdit)
	{
		switch (logLevel)
		{
		case LogLevelEnum::Normal:
			UE_LOG(LogLoad, Log, TEXT("%s"), *realContent);
			break;
		case LogLevelEnum::Warning:
			UE_LOG(LogLoad, Warning, TEXT("%s"), *realContent);
			break;
		case LogLevelEnum::Error:
			UE_LOG(LogLoad, Error, TEXT("%s"), *realContent);
			break;
		default:
			break;
		}
	}
}
