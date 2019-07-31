#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "AddNextScriptAction.generated.h"

//指令：添加指定章节段的剧本到即将开启的剧本列表中
UCLASS()
class LEAVETHEPAST_API UAddNextScriptAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	FString chapterName;
	int sectionId = 0;
	int paragraphId = 0;
};
