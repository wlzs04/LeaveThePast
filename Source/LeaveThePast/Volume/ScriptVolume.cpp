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
		scriptItemData.chapter = stringArray[0];
		scriptItemData.sectionId = FCString::Atoi(*stringArray[1]);
		scriptItemData.paragraphId = FCString::Atoi(*stringArray[2]);
	}
	else
	{
		LogError(FString::Printf(TEXT("体积%s参数数量不对，也可能是分隔符不对。"), *volumeName));
	}
}

FString AScriptVolume::GetVolumeValue()
{
	FString volumeValue;
	volumeValue.Append(scriptItemData.chapter+TEXT(" "));
	volumeValue.Append(FString::FromInt(scriptItemData.sectionId) + TEXT(" "));
	volumeValue.Append(FString::FromInt(scriptItemData.paragraphId));

	return volumeValue;
}

void AScriptVolume::SetInfo(FScriptItemData newScriptItemData)
{
	scriptItemData = newScriptItemData;
}

FScriptItemData AScriptVolume::GetScriptItemData()
{
	return scriptItemData;
}

void AScriptVolume::VolumeBeginOverlapEventReal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == ADirectorActor::GetInstance())
	{
		UScriptManager::GetInstance()->StartScript(scriptItemData.chapter, scriptItemData.sectionId, scriptItemData.paragraphId);
	}
}
