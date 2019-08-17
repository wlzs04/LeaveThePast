#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "EndBattleAction.generated.h"

//指令：结束战斗
UCLASS()
class LEAVETHEPAST_API UEndBattleAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
};
