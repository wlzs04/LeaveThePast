#include "HelpManager.h"
#include "LogManager.h"
#include "FileHelper.h"
#include "FileManagerGeneric.h" 
#include "Runtime/ImageWrapper/Public/IImageWrapper.h" 
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "ModuleManager.h"
#include "Engine/Texture2D.h"

UHelpManager* UHelpManager::helpManager = nullptr;

void UHelpManager::Init()
{
	UHelpManager::helpManager = this;
}

FVector UHelpManager::ConvertFStringToFVector(FString value)
{
	TArray<FString> stringArray;
	value.ParseIntoArray(stringArray, TEXT(","));
	float x = 0;
	float y = 0;
	float z = 0;
	if (stringArray.Num() == 3)
	{
		x = FCString::Atof(*stringArray[0]);
		y = FCString::Atof(*stringArray[1]);
		z = FCString::Atof(*stringArray[2]);
	}
	else
	{
		LogError(FString::Printf(TEXT("FString->FVector以','分割，格式不对:%s"), *value));
	}
	return FVector(x,y,z);
}

FString UHelpManager::ConvertToFString(FVector value)
{
	return FString::FromInt(value.X) + TEXT(",")+ FString::FromInt(value.Y) + TEXT(",")+ FString::FromInt(value.Z);
}

FString UHelpManager::ConvertToFString(FRotator value)
{
	return FString::FromInt(value.Roll) + TEXT(",") + FString::FromInt(value.Pitch) + TEXT(",") + FString::FromInt(value.Yaw);
}

FString UHelpManager::ConvertToFString(FTimespan value)
{
	return FString::FromInt(value.GetHours()) + TEXT(":") + FString::FromInt(value.GetMinutes()) + TEXT(":") + FString::FromInt(value.GetSeconds());
}

FTimespan UHelpManager::ConvertFStringToFTimespan(FString value)
{
	TArray<FString> stringArray;
	value.ParseIntoArray(stringArray, TEXT(":"));
	float x = 0;
	float y = 0;
	float z = 0;
	if (stringArray.Num() == 3)
	{
		x = FCString::Atof(*stringArray[0]);
		y = FCString::Atof(*stringArray[1]);
		z = FCString::Atof(*stringArray[2]);
	}
	else
	{
		LogError(FString::Printf(TEXT("FString->FTimespan以':'分割，格式不对:%s"), *value));
	}
	return FTimespan(x, y, z);
}

FRotator UHelpManager::ConvertFStringToFRotator(FString value)
{
	TArray<FString> stringArray;
	value.ParseIntoArray(stringArray, TEXT(","));
	float x = 0;
	float y = 0;
	float z = 0;
	if (stringArray.Num() == 3)
	{
		x = FCString::Atof(*stringArray[0]);
		y = FCString::Atof(*stringArray[1]);
		z = FCString::Atof(*stringArray[2]);
	}
	else
	{
		LogError(FString::Printf(TEXT("FString->FRotator以','分割，格式不对:%s"), *value));
	}
	return FRotator(y, z, x);
}

UTexture2D* UHelpManager::LoadTexture2D(FString path, bool& isValid, int32& outWidth, int32& outHeight)
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