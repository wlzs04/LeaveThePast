#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Sound/SoundCue.h"
#include "AudioManager.generated.h"

class USoundClass;
class USoundMix;

UCLASS()
class LEAVETHEPAST_API UAudioManager : public UObject
{
	GENERATED_BODY()
public:
	static UAudioManager* GetInstance();

	void Init();

	UFUNCTION(BlueprintCallable)
	void SetMainSoundVolume(float newVolume);
	UFUNCTION(BlueprintCallable)
	void SetBGMSoundVolume(float newVolume);
	UFUNCTION(BlueprintCallable)
	void SetVoiceSoundVolume(float newVolume);
	UFUNCTION(BlueprintCallable)
	void SetEffectSoundVolume(float newVolume);

	USoundClass* GetMainSoundClass();

	USoundClass* GetBGMSoundClass();

	USoundClass* GetVoiceSoundClass();

	USoundClass* GetEffectSoundClass();

	//获得指定名称的声音
	/*UFUNCTION(BlueprintCallable)
	USoundBase* GetAudioByName(FString audioName);*/

	//获得指定Id的声音
	UFUNCTION(BlueprintCallable)
	USoundCue* GetAudioById(int id);

private:
	//加载指定id的声音
	UFUNCTION(BlueprintCallable)
	USoundCue* LoadAudioById(int id);

	static UAudioManager* audioManager;

	TMap<int, USoundCue*> audioMap;

	UPROPERTY()
	USoundMix* mainSoundMix = nullptr;
	UPROPERTY()
	USoundClass* mainSoundClass = nullptr;
	UPROPERTY()
	USoundClass* bgmSoundClass = nullptr;
	UPROPERTY()
	USoundClass* voiceSoundClass = nullptr;
	UPROPERTY()
	USoundClass* effectSoundClass = nullptr;
};
