#include "ScriptVolume.h"
#include "../Actor/DirectorActor.h"
#include "../Manager/ScriptManager.h"

void AScriptVolume::SetInfo(FScriptRecorderInfo newScriptRecorderIndfo)
{
	scriptRecorderIndfo = newScriptRecorderIndfo;
}

FScriptRecorderInfo AScriptVolume::GetScriptInfo()
{
	return scriptRecorderIndfo;
}

void AScriptVolume::VolumeBeginOverlapEventReal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == ADirectorActor::GetInstance())
	{
		UScriptManager::GetInstance()->StartScript(scriptRecorderIndfo.chapter, scriptRecorderIndfo.sectionId, scriptRecorderIndfo.paragraphId);
	}
}
