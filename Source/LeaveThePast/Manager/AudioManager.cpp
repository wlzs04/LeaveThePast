#include "AudioManager.h"
#include "MainGameManager.h"
#include "LogManager.h"
#include "ConfigManager.h"
#include "../Config/Recorder/AudioRecorder.h"
#include "Sound/SoundMix.h"
#include "AudioDevice.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

UAudioManager* UAudioManager::audioManager = nullptr;

UAudioManager* UAudioManager::GetInstance()
{
	return audioManager;
}

void UAudioManager::Init()
{
	UAudioManager::audioManager = this;
	mainSoundMix = LoadObject<USoundMix>(NULL, TEXT("SoundMix'/Game/GameContent/Audio/MainSoundMix.MainSoundMix'"));
	mainSoundClass = LoadObject<USoundClass>(NULL, TEXT("SoundClass'/Game/GameContent/Audio/MainSoundClass.MainSoundClass'"));
	bgmSoundClass = LoadObject<USoundClass>(NULL, TEXT("SoundClass'/Game/GameContent/Audio/BGMSoundClass.BGMSoundClass'"));
	voiceSoundClass = LoadObject<USoundClass>(NULL, TEXT("SoundClass'/Game/GameContent/Audio/VoiceSoundClass.VoiceSoundClass'"));
	effectSoundClass = LoadObject<USoundClass>(NULL, TEXT("SoundClass'/Game/GameContent/Audio/EffectSoundClass.EffectSoundClass'"));
}

void UAudioManager::SetMainSoundVolume(float newVolume)
{
	newVolume = FMath::Clamp(newVolume,0.001f,1.0f);
	UGameplayStatics::SetSoundMixClassOverride(this, mainSoundMix, mainSoundClass, newVolume, 1, 0, true);
	UMainGameManager::GetInstance()->GetSystemData()->SetMainSoundVolume(newVolume);
}

void UAudioManager::SetBGMSoundVolume(float newVolume)
{
	newVolume = FMath::Clamp(newVolume, 0.001f, 1.0f);
	UGameplayStatics::SetSoundMixClassOverride(this, mainSoundMix, bgmSoundClass, newVolume, 1, 0, true);
	UMainGameManager::GetInstance()->GetSystemData()->SetBGMSoundVolume(newVolume);
}

void UAudioManager::SetVoiceSoundVolume(float newVolume)
{
	newVolume = FMath::Clamp(newVolume, 0.001f, 1.0f);
	UGameplayStatics::SetSoundMixClassOverride(this, mainSoundMix, voiceSoundClass, newVolume, 1, 0, true);
	UMainGameManager::GetInstance()->GetSystemData()->SetVoiceSoundVolume(newVolume);
}

void UAudioManager::SetEffectSoundVolume(float newVolume)
{
	UGameplayStatics::SetSoundMixClassOverride(this, mainSoundMix, effectSoundClass, newVolume, 1, 0, true);
	UMainGameManager::GetInstance()->GetSystemData()->SetEffectSoundVolume(newVolume);
}

USoundClass* UAudioManager::GetMainSoundClass()
{
	return mainSoundClass;
}

USoundClass* UAudioManager::GetBGMSoundClass()
{
	return bgmSoundClass;
}

USoundClass* UAudioManager::GetVoiceSoundClass()
{
	return voiceSoundClass;
}

USoundClass* UAudioManager::GetEffectSoundClass()
{
	return effectSoundClass;
}


USoundCue* UAudioManager::GetAudioById(int id)
{
	if (audioMap.Contains(id))
	{
		return audioMap[id];
	}
	else
	{
		return LoadAudioById(id);
	}
}

USoundCue* UAudioManager::LoadAudioById(int id)
{
	UAudioRecorder* audioRecorder = (UAudioRecorder*)(UConfigManager::GetInstance()->GetConfigByNameId(UAudioRecorder::StaticClass(), TEXT("Audio"),id));
	//因为在配置文件中audioName属性可能包含路径，所以先将真实名称截取出来。
	/*int lastCharIndex = 0;
	audioName.FindLastChar(TEXT('/'), lastCharIndex);
	FString realAudioName = audioName.Right(audioName.Len() - lastCharIndex - 1);
	audioRecorder->GetAudioRootPath*/
	FString audioPath = TEXT("SoundCue'/Game/" + audioRecorder->GetAudioRootPath() + TEXT("/") + audioRecorder->GetAudioName() + "." + audioRecorder->GetAudioName() + "'");
	USoundCue* sound = LoadObject<USoundCue>(nullptr, *audioPath);
	if (!sound)
	{
		LogError(audioPath + TEXT("加载失败！"));
	}
	else
	{
		audioMap.Add(id, sound);
	}
	return sound;
}