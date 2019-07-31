#include "AudioRecorder.h"

void UAudioRecorder::LoadRecorder(FXmlNode* xmlNode)
{
	URecorderBase::LoadRecorder(xmlNode);

	audioName = xmlNode->GetAttribute(TEXT("audioName"));
	audioType = FCString::Atoi(*xmlNode->GetAttribute(TEXT("audioType")));
	audioRootPath = xmlNode->GetAttribute(TEXT("audioRootPath"));
}

FString UAudioRecorder::GetAudioName()
{
	return audioName;
}

int UAudioRecorder::GetAudioType()
{
	return audioType;
}

FString UAudioRecorder::GetAudioRootPath()
{
	return audioRootPath;
}
