#include "RecorderBase.h"
#include "./Manager/LogManager.h"

void URecorderBase::LoadRecorder(FXmlNode* xmlNode)
{
	LogError(TEXT("配置没有重写LoadRecorder方法！"));
}

int URecorderBase::GetId()
{
	return id;
}