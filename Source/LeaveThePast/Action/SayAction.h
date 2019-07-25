#pragma once

#include "CoreMinimal.h"
#include "ActionBase.h"
#include "SayAction.generated.h"

UCLASS()
class LEAVETHEPAST_API USayAction : public UActionBase
{
	GENERATED_BODY()
public:
	USayAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
	virtual void Finish() override;
private:
	FString text = TEXT("无内容！");
	FString voicePath = TEXT("");
	float actionTime = 1;

	float currentTime = 0;
	float startTime = 0;
};