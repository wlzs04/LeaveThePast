#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <LeaveThePast\Public\Action\ActionBase.h>
#include "Paragraph.generated.h"

UCLASS()
class LEAVETHEPAST_API UParagraph : public UObject
{
	GENERATED_BODY()
public:
	void Update();
	void Load(FXmlNode* xmlNode);
	bool GetIsCompleted();
	void Start();
private:
	TArray<UActionBase*> actionList;
	bool isCompleted = false;//是否完成
	bool isStart = false;//是否开始
	int currentActionIndex = 0;
};