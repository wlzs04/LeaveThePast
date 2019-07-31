#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XmlParser/Public/XmlFile.h"
#include "ActionBase.generated.h"

//指令基类
UCLASS(BlueprintType)
class LEAVETHEPAST_API UActionBase : public UObject
{
	GENERATED_BODY()
public:
	UActionBase();
	FString GetActionName();
	virtual void Update() {};
	FString Execute();
	void Finish();
	//xml格式
	virtual void Load(FXmlNode* xmlNode);
	//string格式
	virtual void Load(TArray<FString> paramList);
	bool GetIsCompleted();

	//跳过指令
	virtual bool SkipAction();
protected:
	//子类重写执行方法
	virtual FString ExecuteReal();
	//子类重写指令完成方法
	virtual void FinishReal();

	FString actionName = TEXT("未命名指令");//指令名称
	bool isCompleted = false;//是否完成
	bool isStart = false;//是否开始
};
