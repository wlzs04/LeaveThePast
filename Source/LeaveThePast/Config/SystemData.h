#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SystemData.generated.h"

UCLASS()
class LEAVETHEPAST_API USystemData : public UObject
{
	GENERATED_BODY()
public:
	USystemData();

	void Load();

	void Save();

	UFUNCTION(BlueprintCallable)
	bool GetShowInitUI();
	UFUNCTION(BlueprintCallable)
	void SetShowInitUI(bool newShowInitUI);

	UFUNCTION(BlueprintCallable)
	bool GetMissionAccomplished();
	UFUNCTION(BlueprintCallable)
	void SetMissionAccomplished(bool newMissionAccomplished);

	UFUNCTION(BlueprintCallable)
	float GetBackgroundSoundVolume();
	UFUNCTION(BlueprintCallable)
	void SetBackgroundSoundVolume(float newBackgroundSoundVolume);

	UFUNCTION(BlueprintCallable)
	float GetVoiceSoundVolume();
	UFUNCTION(BlueprintCallable)
	void SetVoiceSoundVolume(float newVoiceSoundVolume);

	UFUNCTION(BlueprintCallable)
	float GetEffectSoundVolume();
	UFUNCTION(BlueprintCallable)
	void SetEffectSoundVolume(float newEffectSoundVolume);
private:
	//保存路径
	FString savePath;
	//是否显示初始界面
	bool showInitUI = true;
	//是否游戏通关
	bool missionAccomplished = false;
	//背景音量
	float backgroundSoundVolume = 1;
	//语音音量
	float voiceSoundVolume = 1;
	//效果音量
	float effectSoundVolume = 1;
};
