#include "ConfigManager.h"
#include "LogManager.h"
#include "Runtime/XmlParser/Public/XmlParser.h"
#include "Runtime/XmlParser/Public/FastXml.h" 
#include "XmlParser/Public/XmlFile.h"
#include "LogMacros.h"
#include "Paths.h"
#include "UObjectGlobals.h"

UConfigManager* UConfigManager::configManager = nullptr;

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

UConfigManager* UConfigManager::GetInstance()
{
	return UConfigManager::configManager;
}

void UConfigManager::Init()
{
	UConfigManager::configManager = this;
}

TMap<int, URecorderBase*> UConfigManager::GetConfigByName(UClass* recorderClass)
{
	if (recorderClass == nullptr)
	{
		LogError(FString::Printf(TEXT("未选择Recorder类型！")));
		return TMap<int, URecorderBase*>();
	}
	FString configName = recorderClass->GetName();
	configName = configName.Left(configName.Len() - 8);

	if (!configMap.Contains(configName))
	{
		LoadConfigByName(recorderClass);
	}
	if (!configMap.Contains(configName))
	{
		LogError(FString::Printf(TEXT("配置文件加载失败：%s"), *configName));
		return TMap<int, URecorderBase*>();
	}
	return *configMap[configName];
}

URecorderBase* UConfigManager::GetConfigByNameId(UClass* recorderClass, int id)
{
	TMap<int, URecorderBase*> recorderMap = GetConfigByName(recorderClass);
	if (recorderMap.Contains(id))
	{
		return recorderMap[id];
	}
	return nullptr;
}

void UConfigManager::LoadConfigByName(UClass* recorderClass)
{
	if (recorderClass == nullptr)
	{
		LogError(FString::Printf(TEXT("未选择Recorder类型！")));
		return;
	}
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
		LogError(FString::Printf(TEXT("配置文件加载失败：%s"), *configPath));
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
	LogNormal(FString::Printf(TEXT("配置文件加载完成：%s"), *configPath));
}
