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
		for (FXmlAttribute attribute : rootNode->GetAttributes())
		{
			FString attributeName = attribute.GetTag();
			FString attributeValue = attribute.GetValue(); 
			
			if (attributeName == TEXT("showInitUI"))
			{
				showInitUI = attributeValue.ToBool();
			}
			else if (attributeName == TEXT("missionAccomplished"))
			{
				missionAccomplished = attributeValue.ToBool();
			}
			else if (attributeName == TEXT("mainSoundVolume"))
			{
				mainSoundVolume = FCString::Atof(*attributeValue);
			}
			else if(attributeName == TEXT("bgmSoundVolume"))
			{
				bgmSoundVolume = FCString::Atof(*attributeValue);
			}
			else if (attributeName == TEXT("voiceSoundVolume"))
			{
				voiceSoundVolume = FCString::Atof(*attributeValue);
			}
			else if (attributeName == TEXT("effectSoundVolume"))
			{
				effectSoundVolume = FCString::Atof(*attributeValue);
			}
			else
			{
				LogWarning(FString::Printf(TEXT("系统存档中存在未知属性：%s:%s"), *attributeName, *attributeValue));
			}
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
	FString showInitUIString = (showInitUI ? TEXT("true") : TEXT("false"));
	xmlContent.Append(TEXT("showInitUI=\"") + showInitUIString + TEXT("\" "));
	FString missionAccomplishedString = (missionAccomplished ? TEXT("true") : TEXT("false"));
	xmlContent.Append(TEXT("missionAccomplished=\"") + missionAccomplishedString + TEXT("\" "));
	xmlContent.Append(TEXT("mainSoundVolume=\"") + FString::SanitizeFloat(mainSoundVolume) + TEXT("\" "));
	xmlContent.Append(TEXT("bgmSoundVolume=\"") + FString::SanitizeFloat(bgmSoundVolume) + TEXT("\" "));
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

bool USystemData::GetShowInitUI()
{
	return 	showInitUI;
}

void USystemData::SetShowInitUI(bool newShowInitUI)
{
	showInitUI = newShowInitUI;
}

bool USystemData::GetMissionAccomplished()
{
	return missionAccomplished;
}

void USystemData::SetMissionAccomplished(bool newMissionAccomplished)
{
	missionAccomplished = newMissionAccomplished;
}

float USystemData::GetMainSoundVolume()
{
	return mainSoundVolume;
}

void USystemData::SetMainSoundVolume(float newMainSoundVolume)
{
	mainSoundVolume = newMainSoundVolume;
}

float USystemData::GetBGMSoundVolume()
{
	return bgmSoundVolume;
}

void USystemData::SetBGMSoundVolume(float newBGMSoundVolume)
{
	bgmSoundVolume = newBGMSoundVolume;
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
