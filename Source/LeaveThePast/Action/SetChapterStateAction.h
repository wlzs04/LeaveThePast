#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetChapterStateAction.generated.h"

//指令：设置剧情中指定章的状态，一般用于标记此章是否完成
UCLASS()
class LEAVETHEPAST_API USetChapterStateAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	FString chapter;
	int state = 0;
	bool isCurrent = true;
};
