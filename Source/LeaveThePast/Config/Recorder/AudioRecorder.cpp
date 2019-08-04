#include "AudioRecorder.h"
#include "../../Manager/LogManager.h"

void UAudioRecorder::LoadRecorder(FXmlNode* xmlNode)
{
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("id"))
		{
			id = FCString::Atoi(*attributeValue);
		}
		else if(attributeName == TEXT("name"))
		{
			audioName = attributeValue;
		}
		else if (attributeName == TEXT("type"))
		{
			audioType = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("rootPath"))
		{
			audioRootPath = attributeValue;
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s配置中存在未知属性:%s：%s！"), *GetClass()->GetName().Left(GetClass()->GetName().Len() - 8), *attributeName, *attributeValue));
		}
	}
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
