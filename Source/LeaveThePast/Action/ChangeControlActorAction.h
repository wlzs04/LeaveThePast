#pragma once

#include "CoreMinimal.h"
#include "ActionBase.h"
#include "ChangeControlActorAction.generated.h"

//指令：改变玩家控制的演员
UCLASS()
class LEAVETHEPAST_API UChangeControlActorAction : public UActionBase
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
