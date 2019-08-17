#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "EnterBattleAction.generated.h"

//指令：进入战斗
UCLASS()
class LEAVETHEPAST_API UEnterBattleAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
};
