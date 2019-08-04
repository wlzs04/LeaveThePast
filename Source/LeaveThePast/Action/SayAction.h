#pragma once

#include "CoreMinimal.h"
#include "ActionBase.h"
#include "SayAction.generated.h"

class AActorBase;

//指令：演员说话，显示谈话界面
UCLASS()
class LEAVETHEPAST_API USayAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
	virtual void FinishReal() override;
private:
	int actorInfoId = 0;
	FString text = TEXT("无内容！");
	FString voicePath = TEXT("");
	float actionTime = 1;

	bool isPlayerControlActorId = true;
	float currentTime = 0;
	UPROPERTY()
	AActorBase* executeActor = nullptr;
};