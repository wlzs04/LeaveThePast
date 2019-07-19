#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "..\Config\Recorder\SceneRecorder.h"
#include "NewActorAction.generated.h"

/**
 * 
 */
UCLASS()
class LEAVETHEPAST_API UNewActorAction : public UActionBase
{
	GENERATED_BODY()
public:
	UNewActorAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;
private:
	FSceneActorInfo sceneActorInfo;
};
