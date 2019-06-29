#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "ChangeCameraActorAction.generated.h"

UCLASS()
class LEAVETHEPAST_API UChangeCameraActorAction : public UActionBase
{
	GENERATED_BODY()
public:
	UChangeCameraActorAction();
	//加载内容
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;
};
