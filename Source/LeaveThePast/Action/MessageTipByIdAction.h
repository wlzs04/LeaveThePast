#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "MessageTipByIdAction.generated.h"

//指令：显示提示界面，显示指令表中id对应提示
UCLASS()
class LEAVETHEPAST_API UMessageTipByIdAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:
	int messageId = 0;
	float actionTime = 1;

	float currentTime = 0;
	
};
