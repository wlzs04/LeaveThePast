#include "MessageTipRecorder.h"

void UMessageTipRecorder::LoadRecorder(FXmlNode* xmlNode)
{
	URecorderBase::LoadRecorder(xmlNode);

	value = xmlNode->GetAttribute(TEXT("value"));
}

FString UMessageTipRecorder::GetValue()
{
	return value;
}
