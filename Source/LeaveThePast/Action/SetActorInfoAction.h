#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "..\Config\Recorder\SceneRecorder.h"
#include "SetActorInfoAction.generated.h"

UCLASS()
class LEAVETHEPAST_API USetActorInfoAction : public UActionBase
{
	GENERATED_BODY()
public:
	USetActorInfoAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;
private:
	FSceneActorInfo sceneActorInfo;
};
