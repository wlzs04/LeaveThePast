#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XmlParser/Public/XmlFile.h"
#include "ActionBase.generated.h"

class AActorBase;

UCLASS()
class LEAVETHEPAST_API UActionBase : public UObject
{
	GENERATED_BODY()
public:
	//初始化，清空已完成等状态
	void Init();
	int GetActorId();
	FString GetActionName();
	virtual void Update() {};
	void Execute();
	virtual void Load(FXmlNode* xmlNode);
	virtual void Load(TArray<FString> paramList);
	bool GetIsCompleted();
	AActorBase* GetExecuteActor();
protected:

	//加载内容
	virtual void ExecuteReal() {};

	FString actionName = TEXT("未命名指令");//指令名称
	bool isCompleted = false;//是否完成
private:
	//由文件配置的属性
	int actorId = 0;//执行指令的演员的Id
	bool isAsync = false;//是否此指令执行的同时执行下一条指令

	AActorBase* executeActor = nullptr;
};
