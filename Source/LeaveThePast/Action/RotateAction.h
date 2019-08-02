#pragma once

#include "CoreMinimal.h"
#include "ActionBase.h"
#include "RotateAction.generated.h"

class AActorBase;

//指令：控制演员旋转
UCLASS()
class LEAVETHEPAST_API URotateAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
	virtual void FinishReal() override;

private:
	int actorInfoId = 0;
	float actionTime = 1;
	//转身角度，默认Z方向，人正常转身的方向
	float value = 0;
	float remainValue = 0;

	bool isPlayerControlActorId = true;
	float currentTime = 0;
	float lastTime = 0;
	UPROPERTY()
	AActorBase* executeActor = nullptr;
};
