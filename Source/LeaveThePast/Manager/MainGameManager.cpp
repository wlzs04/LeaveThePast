#include "MainGameManager.h"
#include "Kismet/KismetSystemLibrary.h"

#include "FileManagerGeneric.h" 
#include "Runtime/ImageWrapper/Public/IImageWrapper.h" 
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "ModuleManager.h"
#include "FileHelper.h"
#include "Engine/Texture2D.h"
#include "LogMacros.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#include "../Action/MoveAction.h"
#include "../Action/SayAction.h"
#include "../Action/RotateAction.h"
#include "../Action/ChangeCameraActorAction.h"
#include "../Action/MessageTipAction.h"
#include "../Action/PlayBGMAction.h"
#include "../Actor/DirectorActor.h"
#include "../Config/Recorder/MessageTipRecorder.h"

UTimeData::UTimeData()
{
	gameDuringSecond = 0;
}

UTimeData::~UTimeData()
{

}

void UTimeData::Tick(float secondTime)
{
	gameDuringSecond += secondTime;
}

float UTimeData::GetHours()
{
	return (int)GetAllHours() % 24;
}

float UTimeData::GetAllHours()
{
	return gameDuringSecond / 3600;
}

float UTimeData::GetMinutes()
{
	return (int)GetAllMinutes() % 60;
}

float UTimeData::GetAllMinutes()
{
	return gameDuringSecond / 60;
}

float UTimeData::GetSeconds()
{
	return ((int)gameDuringSecond) % 60;
}

float UTimeData::GetAllSeconds()
{
	return gameDuringSecond;
}

float UTimeData::GetMilliseconds()
{
	return (gameDuringSecond - (int)gameDuringSecond) * 1000;
}

float UTimeData::GetAllMilliseconds()
{
	return gameDuringSecond * 1000;
}

void UTimeData::SetTime(int hour, int minute, int second)
{
	second = FMath::Clamp(second, 0, 59);
	gameDuringSecond = second;
	minute = FMath::Clamp(minute, 0, 59);
	gameDuringSecond += minute * 60;
	hour = FMath::Max(0, hour);
	gameDuringSecond += hour * 3600;
}

UMainGameManager* UMainGameManager::gameManager = nullptr;

UMainGameManager* UMainGameManager::GetInstance()
{
	return UMainGameManager::gameManager;
}

void UMainGameManager::InitAll()
{
	if (!haveInited)
	{
		UMainGameManager::gameManager = this;
		InitGameTime();
		InitManager();
		LoadSystemData();
		LoadUserData();
		haveInited = true;
	}
}

void UMainGameManager::InitManager()
{
	logManager = NewObject<ULogManager>(this);
	logManager->Init();

	configManager = NewObject<UConfigManager>(this);
	configManager->Init();

	audioManager = NewObject<UAudioManager>(this);
	audioManager->Init();

	LoadIegalAction();
	scriptManager = NewObject<UScriptManager>(this);
	scriptManager->Init();

	actorManager = NewObject<UActorManager>(this); 
	actorManager->Init();

	uiManager = NewObject<UUIManager>(this);
	uiManager->Init();
}

void UMainGameManager::LoadIegalAction()
{
	AddIegalAction(NewObject<UMoveAction>(this));
	AddIegalAction(NewObject<USayAction>(this));
	AddIegalAction(NewObject<URotateAction>(this));
	AddIegalAction(NewObject<UChangeCameraActorAction>(this));
	AddIegalAction(NewObject<UMessageTipAction>(this));
	AddIegalAction(NewObject<UPlayBGMAction>(this));
}

void UMainGameManager::InitGameTime()
{
	realTimeData = NewObject<UTimeData>(this);
	gameTimeData = NewObject<UTimeData>(this);
	StartTime();
}

void UMainGameManager::StartTime()
{
	startTime = true;
}

void UMainGameManager::StopTime()
{
	startTime = false;
}

bool UMainGameManager::IsStartTime()
{
	return startTime;
}

UTimeData* UMainGameManager::GetRealDuringTime()
{
	return realTimeData;
}

UTimeData* UMainGameManager::GetGameDuringTime()
{
	return gameTimeData;
}

void UMainGameManager::SetGameAndRealTimeRate(float newGameAndRealTimeRate)
{
	gameAndRealTimeRate = newGameAndRealTimeRate;
}

float UMainGameManager::GetGameAndRealTimeRate()
{
	return gameAndRealTimeRate;
}

void UMainGameManager::Tick(float secondTime)
{
	if (startTime)
	{
		realTimeData->Tick(secondTime);
		if (!isFixedTime)
		{
			gameTimeData->Tick(secondTime * gameAndRealTimeRate);
		}
		scriptManager->Tick();
	}
}

void UMainGameManager::LoadSystemData()
{
	systemData = NewObject<USystemData>(this);
	systemData->Load();
}

void UMainGameManager::SaveSystemData()
{
	systemData->Save();
}

USystemData* UMainGameManager::GetSystemData()
{
	return systemData;
}

void UMainGameManager::LoadUserData()
{
	userData = NewObject<UUserData>(this);
	userData->Load();
	gameTimeData->SetTime(userData->GetHour(), userData->GetMinute(), userData->GetSecond());
	SetIsFixedTime(userData->GetIsFixedTime());
	SetGameAndRealTimeRate(userData->GetGameAndRealTimeRate());
}

void UMainGameManager::SaveUserData()
{
	userData->Save();
}

UUserData* UMainGameManager::GetUserData()
{
	return userData;
}

void UMainGameManager::SetIsFixedTime(bool newIsFixedTime)
{
	isFixedTime = newIsFixedTime;
}

bool UMainGameManager::GetIsFixedTime()
{
	return isFixedTime;
}

void UMainGameManager::ExitGame()
{
	SaveUserData();
	SaveSystemData();
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

UConfigManager* UMainGameManager::GetConfigManager()
{
	return configManager;
}

UScriptManager* UMainGameManager::GetScriptManager()
{
	return scriptManager;
}

UActorManager* UMainGameManager::GetActorManager()
{
	return actorManager;
}

ULogManager* UMainGameManager::GetLogManager()
{
	return logManager;
}

UUIManager* UMainGameManager::GetUIManager()
{
	return uiManager;
}

UAudioManager* UMainGameManager::GetAudioManager()
{
	return audioManager;
}

FString UMainGameManager::GetArtresPath()
{
	return FPaths::ProjectContentDir() + TEXT("GameContent/Artres/");
}

UTexture2D* UMainGameManager::LoadTexture2D(FString path, bool& isValid, int32& outWidth, int32& outHeight)
{
	path = FPaths::ProjectContentDir() + path;
	UTexture2D* texture = nullptr;
	isValid = false;
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*path))
	{
		return nullptr;
	}
	TArray<uint8> RawFileData;
	if (!FFileHelper::LoadFileToArray(RawFileData, *path))
	{
		return nullptr;
	}
	TSharedPtr<IImageWrapper> ImageWrapper;
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	if (path.EndsWith(".png"))
	{
		ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
	}
	else if (path.EndsWith(".jpg") || path.EndsWith(".jpeg"))
	{
		ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
	}
	else if (path.EndsWith(".bmp"))
	{
		ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::BMP);
	}
	else if (path.EndsWith(".ico"))
	{
		ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::ICO);

	}
	else if (path.EndsWith("exr"))
	{
		ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::EXR);
	}
	else if (path.EndsWith(".icns"))
	{
		ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::ICNS);
	}
	else
	{
		LogError(FString::Printf(TEXT("未知图片文件加载失败：%s"), *path));
	}
	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
	{
		const TArray<uint8>* UncompressedRGBA = nullptr;
		if (ImageWrapper->GetRaw(ERGBFormat::RGBA, 8, UncompressedRGBA))
		{
			texture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_R8G8B8A8);
			
			if (texture != nullptr)
			{
				isValid = true;
				outWidth = ImageWrapper->GetWidth();
				outHeight = ImageWrapper->GetHeight();
				void* TextureData = texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(TextureData, UncompressedRGBA->GetData(), UncompressedRGBA->Num());
				texture->PlatformData->Mips[0].BulkData.Unlock();
				texture->UpdateResource();
			}
		}
	}
	return texture;
}

void UMainGameManager::AddIegalAction(UActionBase* actionBase)
{
	legalActionMap.Add(actionBase->GetActionName(), actionBase);
}

UActionBase* UMainGameManager::GetIegalActionByName(FString actionName)
{
	if (legalActionMap.Contains(actionName))
	{
		return legalActionMap[actionName];
	}
	return nullptr;
}

//void UMainGameManager::AddMessageTip(FString value)
//{
//	AddMessageTip_BPEvent(value);
//}
//
//void UMainGameManager::AddMessageTipById(int id)
//{
//	FString value = TEXT("");
//
//	URecorderBase* messageTipRecorder = configManager->GetConfigByNameId(UMessageTipRecorder::StaticClass(),id);
//	if (messageTipRecorder != nullptr)
//	{
//		value = ((UMessageTipRecorder*)messageTipRecorder)->GetValue();
//	}
//
//	AddMessageTip(value);
//}
//
//void UMainGameManager::SetTalkUI(FString talkValue, FString actorName, float continueTime, FString headImagePath, bool isLeft)
//{
//	SetTalkUI_BPEvent(talkValue, actorName, continueTime, headImagePath, isLeft);
//}
