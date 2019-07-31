#include "ActionBase.h"
#include "../Manager/LogManager.h"

UActionBase::UActionBase()
{
	actionName = GetClass()->GetName().Left(GetClass()->GetName().Len() - 6);
}

FString UActionBase::GetActionName()
{
	return actionName;
}

FString UActionBase::Execute()
{
	isStart = true;
	isCompleted = false;
	LogNormal(actionName + TEXT("指令开始执行！"));
	return ExecuteReal();
}

void UActionBase::Finish()
{
	isStart = false;
	isCompleted = true;
	LogNormal(actionName + TEXT("指令开始结束！"));
	FinishReal();
}

void UActionBase::Load(FXmlNode* xmlNode)
{
	LogError(FString::Printf(TEXT("%s指令无法从Xml中加载信息，需要重写加载方法。"), *actionName));
}

void UActionBase::Load(TArray<FString> paramList)
{
	LogError(FString::Printf(TEXT("%s指令无法从String中加载信息，需要重写加载方法。"), *actionName));
}

bool UActionBase::GetIsCompleted()
{
	return isCompleted;
}

bool UActionBase::SkipAction()
{
	if (!isStart)
	{
		Execute();
	}
	Finish();
	return true;
}

FString UActionBase::ExecuteReal()
{
	LogError(FString::Printf(TEXT("指令%s未重写ExecuteReal方法。"), *actionName));
	return FString();
}

void UActionBase::FinishReal()
{
	
}