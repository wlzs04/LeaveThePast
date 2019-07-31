#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "..\Config\Recorder\SceneRecorder.h"
#include "AddActorAction.generated.h"

//指令：添加演员到场景中
UCLASS()
class LEAVETHEPAST_API UAddActorAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:
	FSceneActorInfo sceneActorInfo;
};
