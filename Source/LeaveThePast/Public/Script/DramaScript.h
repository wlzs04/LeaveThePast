#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Action/ActionBase.h"
#include "DramaScript.generated.h"

UCLASS()
class LEAVETHEPAST_API UDramaScript : public UObject
{
	GENERATED_BODY()
public:
	void Update();
	void Load(FString newScriptPath);
	bool GetIsCompleted();
	void Start();
private:
	TArray<UActionBase*> actionList;
	bool isCompleted = false;//是否完成
	bool isStart = false;//是否开始
	int currentActionIndex = 0;

	FString scriptPath = TEXT("");
};
