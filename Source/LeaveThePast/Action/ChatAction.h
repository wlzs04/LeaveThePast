#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "ChatAction.generated.h"

class AActorBase;

//指令：演员闲话，显示小型闲话框
UCLASS()
class LEAVETHEPAST_API UChatAction : public UActionBase
{
	GENERATED_BODY()
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

	bool isPlayerControlActorId = true;
	float currentTime = 0;
	UPROPERTY()
	AActorBase* executeActor = nullptr;
};
