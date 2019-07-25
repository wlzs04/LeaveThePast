#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XmlParser/Public/XmlFile.h"
#include "ActionBase.generated.h"

class AActorBase;

UCLASS(BlueprintType)
class LEAVETHEPAST_API UActionBase : public UObject
{
	GENERATED_BODY()
public:
	//初始化，清空已完成等状态
	void Init();
	int GetActorInfoId();
	FString GetActionName();
	virtual void Update() {};
	FString Execute();
	virtual void Finish();
	//xml格式
	virtual void Load(FXmlNode* xmlNode);
	//string格式
	virtual void Load(TArray<FString> paramList);
	bool GetIsCompleted();
	AActorBase* GetExecuteActor();

	//跳过指令
	virtual bool SkipAction();
protected:
	//加载内容
	virtual FString ExecuteReal() { return FString(TEXT("")); };

	FString actionName = TEXT("未命名指令");//指令名称
	bool isCompleted = false;//是否完成
private:
	//由文件配置的属性
	int actorInfoId = 0;//执行指令的演员的信息Id
	bool isAsync = false;//是否此指令执行的同时执行下一条指令

	AActorBase* executeActor = nullptr;
};
