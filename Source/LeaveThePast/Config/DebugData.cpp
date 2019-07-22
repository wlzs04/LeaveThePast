#include "DebugData.h"
#include "Paths.h"
#include "XmlParser/Public/XmlFile.h"
#include "../Manager/LogManager.h"

UDebugData::UDebugData() :UObject()
{
	savePath = FPaths::ProjectContentDir() + TEXT("GameContent/Artres/Config/DebugData.xml");
}

void UDebugData::Load()
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

			if (attributeName == TEXT("showCollision"))
			{
				showCollision = attributeValue.ToBool();
			}
			else if (attributeName == TEXT("showFPS"))
			{
				showFPS = attributeValue.ToBool();
			}
			else
			{
				LogWarning(FString::Printf(TEXT("调试存档中存在未知属性：%s:%s"), *attributeName, *attributeValue));
			}
		}
	}

	xmlFile->Clear();
	delete xmlFile;
	LogNormal(FString::Printf(TEXT("Save文件：%s加载完成！"), *savePath));
}

void UDebugData::Save()
{
	FString xmlContent = TEXT("<DebugData ");
	//start 添加基础信息
	FString showCollisionString = (showCollision ? TEXT("true") : TEXT("false"));
	xmlContent.Append(TEXT("showCollision=\"") + showCollisionString + TEXT("\" "));
	//end 添加基础信息
	xmlContent.Append(TEXT(">\n"));
	xmlContent.Append(TEXT("</DebugData>"));

	FXmlFile* xmlFile = new FXmlFile(xmlContent, EConstructMethod::ConstructFromBuffer);
	xmlFile->Save(savePath);
	xmlFile->Clear();
	delete xmlFile;
}

bool UDebugData::GetShowCollision()
{
	return showCollision;
}

void UDebugData::SetShowCollision(bool newShowCollision)
{
	showCollision = newShowCollision;
}

bool UDebugData::GetShowFPS()
{
	return showFPS;
}

void UDebugData::SetShowFPS(bool newShowFPS)
{
	showFPS = newShowFPS;
}
