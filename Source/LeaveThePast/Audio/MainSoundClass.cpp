#include "MainSoundClass.h"
#include "BGMSoundClass.h"
#include "VoiceSoundClass.h"
#include "EffectSoundClass.h"

UMainSoundClass::UMainSoundClass():USoundClass()
{
	ChildClasses.Add(NewObject<UBGMSoundClass>());
	ChildClasses.Add(NewObject<UVoiceSoundClass>());
	ChildClasses.Add(NewObject<UEffectSoundClass>());
}

