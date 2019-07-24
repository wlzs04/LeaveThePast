#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "..\Config\Recorder\SceneRecorder.h"
#include "AddActorAction.generated.h"

UCLASS()
class LEAVETHEPAST_API UAddActorAction : public UActionBase
{
	GENERATED_BODY()
public:
	UAddActorAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:
	FSceneActorInfo sceneActorInfo;
	bool isOnly = false;
};
