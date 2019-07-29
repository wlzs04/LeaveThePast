#pragma once

#include "CoreMinimal.h"
#include "ActionBase.h"
#include "SayAction.generated.h"

class AActorBase;

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
	virtual void FinishReal() override;
private:
	int actorInfoId = 0;
	FString text = TEXT("无内容！");
	FString voicePath = TEXT("");
	float actionTime = 1;

	float currentTime = 0;
	UPROPERTY()
	AActorBase* executeActor = nullptr;
};