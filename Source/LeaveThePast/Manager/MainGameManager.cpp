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

//#include "../Action/MoveAction.h"
//#include "../Action/SayAction.h"
//#include "../Action/RotateAction.h"
//#include "../Action/ChangeCameraActorAction.h"
//#include "../Action/MessageTipAction.h"
//#include "../Action/PlayBGMAction.h"
//#include "../Action/AddItemAction.h"

#include "../Actor/DirectorActor.h"

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
		InitManager();

		realTimeData = NewObject<UTimeData>(this);
		gameTimeData = NewObject<UTimeData>(this);

		systemData = NewObject<USystemData>(this);
		ReloadSystemData();

		userData = NewObject<UUserData>(this);
		ReloadUserData();

		haveInited = true;
	}
}

void UMainGameManager::ReloadSystemData()
{
	systemData->Load();
	GetAudioManager()->SetMainSoundVolume(systemData->GetMainSoundVolume());
	GetAudioManager()->SetBGMSoundVolume(systemData->GetBGMSoundVolume());
	GetAudioManager()->SetVoiceSoundVolume(systemData->GetVoiceSoundVolume());
	GetAudioManager()->SetEffectSoundVolume(systemData->GetEffectSoundVolume());
}

void UMainGameManager::ReloadUserData()
{
	userData->Load();
	gameTimeData->SetTime(userData->GetHour(), userData->GetMinute(), userData->GetSecond());
}

void UMainGameManager::UseItem(int itemId)
{
	if (userData->GetItemNumberById(itemId)>0)
	{
		if (itemId == 20001)
		{
			GetUIManager()->AddMessageTipById(10007);
		}
	}
	userData->ReduceItem(itemId,1);
}

void UMainGameManager::InitManager()
{
	logManager = NewObject<ULogManager>(this);
	logManager->Init();

	configManager = NewObject<UConfigManager>(this);
	configManager->Init();

	audioManager = NewObject<UAudioManager>(this);
	audioManager->Init();

	scriptManager = NewObject<UScriptManager>(this);
	scriptManager->Init();

	actorManager = NewObject<UActorManager>(this); 
	actorManager->Init();

	uiManager = NewObject<UUIManager>(this);
	uiManager->Init();
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

void UMainGameManager::Tick(float secondTime)
{
	if (startTime)
	{
		realTimeData->Tick(secondTime);
		if (!userData->GetIsFixedTime())
		{
			gameTimeData->Tick(secondTime * userData->GetGameAndRealTimeRate());
		}
		scriptManager->Tick();
	}
}

void UMainGameManager::SaveSystemData()
{
	systemData->Save();
}

USystemData* UMainGameManager::GetSystemData()
{
	return systemData;
}

void UMainGameManager::SaveUserData()
{
	userData->Save();
}

UUserData* UMainGameManager::GetUserData()
{
	return userData;
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