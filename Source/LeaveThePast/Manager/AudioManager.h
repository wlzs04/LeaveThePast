#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AudioManager.generated.h"

class USoundBase;

UCLASS()
class LEAVETHEPAST_API UAudioManager : public UObject
{
	GENERATED_BODY()
public:

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

	TMap<int, USoundBase*> audioMap;
};
