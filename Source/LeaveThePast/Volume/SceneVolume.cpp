#include "SceneVolume.h"
#include "../Manager/MainGameManager.h"

void ASceneVolume::VolumeBeginOverlapEventReal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == ADirectorActor::GetInstance())
	{
		UMainGameManager::GetInstance()->EnterScene(sceneId);
		Destroy();
	}
}