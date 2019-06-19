#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SayAction.generated.h"

UCLASS()
class LEAVETHEPAST_API USayAction : public UActionBase
{
	GENERATED_BODY()
public:
	USayAction();
protected:
	//加载内容
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;

private:
	FString text = TEXT("无内容！");
	FString voicePath = TEXT("");
	float actionTime = 1;

	float currentTime = 0;
	float startTime = 0;
};