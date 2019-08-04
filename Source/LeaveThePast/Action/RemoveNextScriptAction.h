#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "RemoveNextScriptAction.generated.h"

//指令：从即将开启的剧本列表中移除指定章节段
UCLASS()
class LEAVETHEPAST_API URemoveNextScriptAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	FString chapterName;
	int sectionId = 0;
	int paragraphId = 0;
};
