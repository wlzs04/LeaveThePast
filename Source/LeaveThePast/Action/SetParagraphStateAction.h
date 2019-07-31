#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetParagraphStateAction.generated.h"

//指令：设置剧情中指定段的状态，一般用于标记此段是否完成
UCLASS()
class LEAVETHEPAST_API USetParagraphStateAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	FString chapter;
	int sectionId = 0;
	int paragraphId = 0;
	int state = 0;
	bool isCurrent = true;
};
