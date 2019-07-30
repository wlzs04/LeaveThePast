#include "ExecuteActionVolume.h"
#include "../Manager/MainGameManager.h"
#include "../Manager/ScriptManager.h"
#include "../Actor/DirectorActor.h"

void AExecuteActionVolume::VolumeBeginOverlapEventReal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == ADirectorActor::GetInstance())
	{
		if (!actionString.IsEmpty())
		{
			UScriptManager::GetInstance()->ExecuteAction(actionString);
			Destroy();
		}
	}
}