#include "RecorderBase.h"

void URecorderBase::LoadRecorder(FXmlNode* xmlNode)
{
	FString idString = xmlNode->GetAttribute(TEXT("id"));
	if (!idString.IsEmpty())
	{
		id = FCString::Atoi(*idString);
	}
}

int URecorderBase::GetId()
{
	return id;
}