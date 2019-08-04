#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "RemoveCanControlActorAction.generated.h"

//指令：移除可控演员，将其设置为不可控，不是从场景中移除
UCLASS()
class LEAVETHEPAST_API URemoveCanControlActorAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:
	int actorInfoId = 0;
};
