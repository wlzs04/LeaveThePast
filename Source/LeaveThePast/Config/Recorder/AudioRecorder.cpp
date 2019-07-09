#include "AudioRecorder.h"

FString UAudioRecorder::GetRecordName()
{
	return TEXT("Audio");
}

FString UAudioRecorder::GetAudioName()
{
	return audioName;
}

FString UAudioRecorder::GetAudioRootPath()
{
	return audioRootPath;
}
