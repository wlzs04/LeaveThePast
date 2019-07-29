#pragma once

#include "CoreMinimal.h"
#include "ActionBase.h"
#include "MoveAction.generated.h"

class AActorBase;

UCLASS()
class LEAVETHEPAST_API UMoveAction : public UActionBase
{
	GENERATED_BODY()
public:
	UMoveAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
	virtual void FinishReal() override;

private:
	int actorInfoId = 0;
	//移动方向
	FVector direction;
	float speed = 100;
	float actionTime = 1;
	FVector remainValue;

	float currentTime = 0;
	UPROPERTY()
	AActorBase* executeActor = nullptr;
};
