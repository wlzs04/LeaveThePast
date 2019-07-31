#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "..\Config\Recorder\SceneRecorder.h"
#include "SetActorInfoAction.generated.h"

//指令：设置演员信息，一般设置位置信息
UCLASS()
class LEAVETHEPAST_API USetActorInfoAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:
	int actorId = 0;
	bool needReplacePosition = false;
	FVector position;
	bool needReplaceRotation = false;
	FRotator rotation;
};
