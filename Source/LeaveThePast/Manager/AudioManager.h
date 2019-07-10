#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AudioManager.generated.h"

class USoundBase;
class USoundClass;

UCLASS()
class LEAVETHEPAST_API UAudioManager : public UObject
{
	GENERATED_BODY()
public:
	static UAudioManager* GetInstance();

	void Init();

	USoundClass* GetMainSoundClass();

	USoundClass* GetBGMSoundClass();

	USoundClass* GetVoiceSoundClass();

	USoundClass* GetEffectSoundClass();

	//获得指定名称的声音
	/*UFUNCTION(BlueprintCallable)
	USoundBase* GetAudioByName(FString audioName);*/

	//获得指定Id的声音
	UFUNCTION(BlueprintCallable)
	USoundBase* GetAudioById(int id);

private:
	//加载指定id的声音
	UFUNCTION(BlueprintCallable)
	USoundBase* LoadAudioById(int id);

	static UAudioManager* audioManager;

	TMap<int, USoundBase*> audioMap;

	UPROPERTY()
	USoundClass* mainSoundClass = nullptr;
	UPROPERTY()
	USoundClass* bgmSoundClass = nullptr;
	UPROPERTY()
	USoundClass* voiceSoundClass = nullptr;
	UPROPERTY()
	USoundClass* effectSoundClass = nullptr;
};
