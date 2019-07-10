#include "AudioManager.h"
#include "LogManager.h"
#include "ConfigManager.h"
#include "../Config/Recorder/AudioRecorder.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundClass.h"
//#include "AudioDeviceManager.h"
#include "Engine/World.h"

UAudioManager* UAudioManager::audioManager = nullptr;

UAudioManager* UAudioManager::GetInstance()
{
	return audioManager;
}

void UAudioManager::Init()
{
	audioManager = this;
	mainSoundClass = LoadObject<USoundClass>(NULL, TEXT("SoundClass'/Game/GameContent/Audio/MainSoundClass.MainSoundClass'"));
	bgmSoundClass = LoadObject<USoundClass>(NULL, TEXT("SoundClass'/Game/GameContent/Audio/BGMSoundClass.BGMSoundClass'"));
	voiceSoundClass = LoadObject<USoundClass>(NULL, TEXT("SoundClass'/Game/GameContent/Audio/VoiceSoundClass.VoiceSoundClass'"));
	effectSoundClass = LoadObject<USoundClass>(NULL, TEXT("SoundClass'/Game/GameContent/Audio/EffectSoundClass.EffectSoundClass'"));
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


USoundBase* UAudioManager::GetAudioById(int id)
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

USoundBase* UAudioManager::LoadAudioById(int id)
{
	UAudioRecorder* audioRecorder = (UAudioRecorder*)(UConfigManager::GetInstance()->GetConfigByNameId(UAudioRecorder::StaticClass(), id));
	//因为在配置文件中audioName属性可能包含路径，所以先将真实名称截取出来。
	/*int lastCharIndex = 0;
	audioName.FindLastChar(TEXT('/'), lastCharIndex);
	FString realAudioName = audioName.Right(audioName.Len() - lastCharIndex - 1);
	audioRecorder->GetAudioRootPath*/
	FString audioPath = TEXT("SoundWave'/Game/" + audioRecorder->GetAudioRootPath() + TEXT("/") + audioRecorder->GetAudioName() + "." + audioRecorder->GetAudioName() + "'");
	USoundBase* sound = LoadObject<USoundBase>(nullptr, *audioPath);
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