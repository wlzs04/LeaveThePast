#include "ScriptItemData.h"
#include "XmlParser/Public/XmlFile.h"
#include "../Manager/LogManager.h"

FScriptItemData::FScriptItemData()
{
    sectionId = 0; 
    paragraphId = 0;
}

FScriptItemData::FScriptItemData(FString newChapter, int newSectionId, int newParagraphId)
{
    chapter = newChapter;
    sectionId = newSectionId;
    paragraphId = newParagraphId;
}

bool FScriptItemData::operator == (const FScriptItemData& anotherData)
{
    return (chapter == anotherData.chapter) &&
        sectionId == anotherData.sectionId &&
        paragraphId == anotherData.paragraphId;
}

void FScriptItemData::LoadFromXmlNode(FXmlNode* xmlNode)
{
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();

		if (attributeName == TEXT("chapter"))
		{
			chapter = attributeValue;
		}
		else if (attributeName == TEXT("sectionId"))
		{
			sectionId = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("paragraphId"))
		{
			paragraphId = FCString::Atoi(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("ScriptItemData中存在未知属性:%s：%s！"), *attributeName, *attributeValue));
		}
	}
}