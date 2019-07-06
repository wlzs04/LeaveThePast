#include "SystemData.h"
#include "Paths.h"
#include "XmlParser/Public/XmlFile.h"
#include "../Manager/LogManager.h"

USystemData::USystemData() :UObject()
{
	savePath = FPaths::ProjectContentDir() + TEXT("GameContent/Artres/Config/SystemData.xml");
}

void USystemData::Load()
{
	FXmlFile* xmlFile = new FXmlFile(savePath);
	if (!xmlFile->IsValid())
	{
		LogError(FString::Printf(TEXT("存档文件加载失败：%s"), *savePath));
		return;
	}

	FXmlNode* rootNode = xmlFile->GetRootNode();

	//加载基础属性
	{
		FString missionAccomplishedString = rootNode->GetAttribute(TEXT("missionAccomplished"));
		if (!missionAccomplishedString.IsEmpty())
		{
			missionAccomplished = missionAccomplishedString.ToBool();
		}
		FString backgroundSoundVolumeString = rootNode->GetAttribute(TEXT("backgroundSoundVolume"));
		if (!backgroundSoundVolumeString.IsEmpty())
		{
			backgroundSoundVolume = FCString::Atof(*backgroundSoundVolumeString);
		}
		FString voiceSoundVolumeString = rootNode->GetAttribute(TEXT("voiceSoundVolume"));
		if (!voiceSoundVolumeString.IsEmpty())
		{
			voiceSoundVolume = FCString::Atof(*voiceSoundVolumeString);
		}
		FString effectSoundVolumeString = rootNode->GetAttribute(TEXT("effectSoundVolume"));
		if (!effectSoundVolumeString.IsEmpty())
		{
			effectSoundVolume = FCString::Atof(*effectSoundVolumeString);
		}
	}

	xmlFile->Clear();
	delete xmlFile;
	LogNormal(FString::Printf(TEXT("Save文件：%s加载完成！"), *savePath));
}

void USystemData::Save()
{
	FString xmlContent = TEXT("<SystemData ");
	//start 添加基础信息
	FString missionAccomplishedString = (missionAccomplished ? TEXT("true") : TEXT("false"));
	xmlContent.Append(TEXT("missionAccomplished=\"") + missionAccomplishedString + TEXT("\" "));
	xmlContent.Append(TEXT("backgroundSoundVolume=\"") + FString::SanitizeFloat(backgroundSoundVolume) + TEXT("\" "));
	xmlContent.Append(TEXT("voiceSoundVolume=\"") + FString::SanitizeFloat(voiceSoundVolume) + TEXT("\" "));
	xmlContent.Append(TEXT("effectSoundVolume=\"") + FString::SanitizeFloat(effectSoundVolume) + TEXT("\" "));
	//end 添加基础信息
	xmlContent.Append(TEXT(">\n"));
	xmlContent.Append(TEXT("</SystemData>"));

	FXmlFile* xmlFile = new FXmlFile(xmlContent, EConstructMethod::ConstructFromBuffer);
	xmlFile->Save(savePath);
	xmlFile->Clear();
	delete xmlFile;
}

bool USystemData::GetMissionAccomplished()
{
	return missionAccomplished;
}

void USystemData::SetMissionAccomplished(bool newMissionAccomplished)
{
	missionAccomplished = newMissionAccomplished;
}

float USystemData::GetBackgroundSoundVolume()
{
	return backgroundSoundVolume;
}

void USystemData::SetBackgroundSoundVolume(float newBackgroundSoundVolume)
{
	backgroundSoundVolume = newBackgroundSoundVolume;
}

float USystemData::GetVoiceSoundVolume()
{
	return voiceSoundVolume;
}

void USystemData::SetVoiceSoundVolume(float newVoiceSoundVolume)
{
	voiceSoundVolume = newVoiceSoundVolume;
}

float USystemData::GetEffectSoundVolume()
{
	return effectSoundVolume;
}

void USystemData::SetEffectSoundVolume(float newEffectSoundVolume)
{
	effectSoundVolume = newEffectSoundVolume;
}
