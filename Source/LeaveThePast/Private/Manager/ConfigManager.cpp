#include "../../public/Manager/ConfigManager.h"
#include "Runtime/XmlParser/Public/XmlParser.h"
#include "Runtime/XmlParser/Public/FastXml.h" 
#include "XmlParser/Public/XmlFile.h"
#include "LogMacros.h"
#include "Paths.h"
#include "UObjectGlobals.h"

UConfigManager::~UConfigManager()
{
	for (auto var : configMap)
	{
		if (var.Value != nullptr)
		{
			delete var.Value;
			var.Value = nullptr;
		}
	}
}

TMap<int, URecorderBase*> UConfigManager::GetConfigByName(UClass* recorderClass)
{
	FString configName = recorderClass->GetName();
	configName = configName.Left(configName.Len() - 8);

	if (!configMap.Contains(configName))
	{
		LoadConfigByName(recorderClass);
	}
	if (!configMap.Contains(configName))
	{
		UE_LOG(LogLoad, Error, TEXT("配置文件加载失败：%s"), *configName);
		return TMap<int, URecorderBase*>();
	}
	return *configMap[configName];
}

void UConfigManager::LoadConfigByName(UClass* recorderClass)
{
	FString configName = recorderClass->GetName();
	configName = configName.Left(configName.Len() - 8);

	if (configMap.Contains(configName))
	{
		return;
	}
	configMap.Add(configName, new TMap<int, URecorderBase*>());

	FString configPath = FPaths::ProjectContentDir() + configRootPath + configName + TEXT(".xml");

	FXmlFile* xmlFile = new FXmlFile(configPath);
	if (!xmlFile->IsValid())
	{
		UE_LOG(LogLoad, Error, TEXT("配置文件加载失败：%s"), *configPath);
		return;
	}

	FXmlNode* rootNode = xmlFile->GetRootNode();

	for (FXmlNode* recorderNode : rootNode->GetChildrenNodes())
	{
		URecorderBase* record = static_cast<URecorderBase*>(StaticConstructObject_Internal(recorderClass, this, NAME_None, RF_NoFlags, EInternalObjectFlags::None, nullptr, false, nullptr));
		record->LoadRecorder(recorderNode);
		configMap[configName]->Add(record->GetId(), record);
	}

	xmlFile->Clear();
	delete xmlFile;
	UE_LOG(LogLoad, Log, TEXT("Save文件：%s加载完成！"), *configPath);
}
