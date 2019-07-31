#include "StringRecorder.h"

void UStringRecorder::LoadRecorder(FXmlNode* xmlNode)
{
	URecorderBase::LoadRecorder(xmlNode);

	value = xmlNode->GetAttribute(TEXT("value"));
}

FString UStringRecorder::GetValue()
{
	return value;
}
