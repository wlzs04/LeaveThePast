#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "PlayBGMAction.generated.h"

//指令：播放背景音乐
UCLASS()
class LEAVETHEPAST_API UPlayBGMAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:
	int audioId = 9;
};
