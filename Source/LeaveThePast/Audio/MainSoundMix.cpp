#include "MainSoundMix.h"

void UMainSoundMix::BeginDestroy()
{
	//Super::BeginDestroy();
}

FString UMainSoundMix::GetDesc(void)
{
	return TEXT("");//Super::GetDesc();
}

#if WITH_EDITOR
void UMainSoundMix::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	//Super::PostEditChangeProperty(PropertyChangedEvent);

#if WITH_EDITORONLY_DATA
	//bChanged = true;
#endif
}
#endif