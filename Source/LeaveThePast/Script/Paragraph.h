#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Paragraph.generated.h"

class UActionBase;
class FXmlNode;

//段
UCLASS()
class LEAVETHEPAST_API UParagraph : public UObject
{
	GENERATED_BODY()
public:
	void Update();
	void Load(FXmlNode* xmlNode);
	bool GetIsCompleted();
	int GetParagraphId();
	bool Start();
	void Finish();
	bool SkipScript();
private:
	TArray<UActionBase*> actionList;
	bool isCompleted = false;//是否完成
	bool isStart = false;//是否开始
	bool canControlMove = false;//在剧本执行中，玩家是否可控制角色移动
	bool canControlView = false;//在剧本执行中，玩家是否可控制角色视野
	bool autoHideMainUI = true;//在剧本执行中，是否自动隐藏主界面
	int paragraphId = 0;
	int currentActionIndex = 0;
};