#pragma once

#include "CoreMinimal.h"
#include "ActionBase.h"
#include "MessageTipAction.generated.h"

//指令：显示提示界面
UCLASS()
class LEAVETHEPAST_API UMessageTipAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:
	FString text = TEXT("无内容！");
	float actionTime = 1;

	float currentTime = 0;
	float startTime = 0;
};
