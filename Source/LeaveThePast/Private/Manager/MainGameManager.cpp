#include "../../public/Manager/MainGameManager.h"
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

#include <LeaveThePast\Public\Action\MoveAction.h>
#include <LeaveThePast\Public\Action\SayAction.h>
#include <LeaveThePast\Public\Action\RotateAction.h>
#include <DirectorActor.h>

void UMainGameManager::InitAll()
{
	if (!haveInited)
	{
		InitGameTime();
		InitManager();
		LoadSystemData();
		LoadUserData();
		haveInited = true;
	}
}

void UMainGameManager::InitManager()
{
	configManager = NewObject<UConfigManager>(this);

	LoadIegalAction();

	dramaScriptManager = NewObject<UDramaScriptManager>(this);
	dramaScriptManager->LoadDramaScriptAll();

	actorManager = NewObject<UActorManager>(this); 
	actorManager->LoadAllActorInfo();
}

void UMainGameManager::LoadIegalAction()
{
	AddIegalAction(NewObject<UMoveAction>(this));
	AddIegalAction(NewObject<USayAction>(this));
	AddIegalAction(NewObject<URotateAction>(this));
}

void UMainGameManager::InitGameTime()
{
	StartTime();
}

void UMainGameManager::BeginGame()
{
	//将所有常驻演员加载到场景中
	//actorManager->LoadAllPermanentActorToScene();

	/*APawn* defaultPawn = GWorld->GetFirstPlayerController<APlayerController>()->GetPawn();
	if (defaultPawn != nullptr)
	{
		ADirectorActor* directorActor = (ADirectorActor*)defaultPawn;
		directorActor->InitActorList();
	}*/
	


	//APlayerController* playerController = GWorld->GetFirstPlayerController<APlayerController>();
	//playerController->SetPawn(mainActor);
	//playerController->SetViewTarget(mainActor);
	//mainActor->AddInputFunction();
	//mainActor->EnableInput(playerController);
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

void UMainGameManager::Tick(float secondTime)
{
	if (startTime)
	{
		dramaScriptManager->Tick();
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
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

UConfigManager* UMainGameManager::GetConfigManager()
{
	return configManager;
}

UDramaScriptManager* UMainGameManager::GetDramaScriptManager()
{
	return dramaScriptManager;
}

UActorManager* UMainGameManager::GetActorManager()
{
	return actorManager;
}

UTexture2D* UMainGameManager::LoadTexture2D(FString path, bool& isValid, int32& outWidth, int32& outHeight)
{
	path = FPaths::ProjectContentDir() + TEXT("GameContent/Data/Texture/") + path;
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
		UE_LOG(LogLoad, Error, TEXT("未知图片文件加载失败：%s"), *path);
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