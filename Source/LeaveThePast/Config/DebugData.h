#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DebugData.generated.h"

UCLASS()
class LEAVETHEPAST_API UDebugData : public UObject
{
	GENERATED_BODY()
public:
	UDebugData();

	void Load();

	void Save();

	UFUNCTION(BlueprintCallable)
	bool GetShowCollision();
	UFUNCTION(BlueprintCallable)
	void SetShowCollision(bool newShowCollision);

	UFUNCTION(BlueprintCallable)
	bool GetShowFPS();
	UFUNCTION(BlueprintCallable)
	void SetShowFPS(bool newShowFPS);

private:
	//保存路径
	FString savePath;

	bool showCollision = false;
	bool showFPS = false;
};
