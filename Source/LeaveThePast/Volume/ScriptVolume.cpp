#include "ScriptVolume.h"
#include "../Actor/DirectorActor.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/LogManager.h"

AScriptVolume::AScriptVolume()
{
	volumeName = TEXT("Script");
	canSave = true;
}

void AScriptVolume::LoadFromString(FString volumeValueString)
{
	TArray<FString> stringArray;
	volumeValueString.ParseIntoArray(stringArray, TEXT(" "));
	if (stringArray.Num() == 3)
	{
		scriptRecorderInfo.chapter = stringArray[0];
		scriptRecorderInfo.sectionId = FCString::Atoi(*stringArray[1]);
		scriptRecorderInfo.paragraphId = FCString::Atoi(*stringArray[2]);
	}
	else
	{
		LogError(FString::Printf(TEXT("体积%s参数数量不对，也可能是分隔符不对。"), *volumeName));
	}
}

FString AScriptVolume::GetVolumeValue()
{
	FString volumeValue;
	volumeValue.Append(scriptRecorderInfo.chapter+TEXT(" "));
	volumeValue.Append(FString::FromInt(scriptRecorderInfo.sectionId) + TEXT(" "));
	volumeValue.Append(FString::FromInt(scriptRecorderInfo.paragraphId));

	return volumeValue;
}

void AScriptVolume::SetInfo(FScriptRecorderInfo newScriptRecorderInfo)
{
	scriptRecorderInfo = newScriptRecorderInfo;
}

FScriptRecorderInfo AScriptVolume::GetScriptInfo()
{
	return scriptRecorderInfo;
}

void AScriptVolume::VolumeBeginOverlapEventReal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == ADirectorActor::GetInstance())
	{
		UScriptManager::GetInstance()->StartScript(scriptRecorderInfo.chapter, scriptRecorderInfo.sectionId, scriptRecorderInfo.paragraphId);
	}
}
