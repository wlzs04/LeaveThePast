#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "AddCanControlActorAction.generated.h"

//指令：添加可控演员
UCLASS()
class LEAVETHEPAST_API UAddCanControlActorAction : public UActionBase
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
