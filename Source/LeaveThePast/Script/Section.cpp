#include "Section.h"
#include "Paragraph.h"
#include "../Manager/LogManager.h"
#include "XmlParser/Public/XmlFile.h"

int USection::GetSectionId()
{
	return sectionId;
}

FString USection::GetSectionName()
{
	return sectionName;
}

FString USection::GetSectionDescription()
{
	return description;
}

TArray<UParagraph*> USection::GetParagraphList()
{
	return paragraphList;
}

void USection::Load(FXmlNode* xmlNode)
{
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("name"))
		{
			sectionName = attributeValue;
		}
		else if (attributeName == TEXT("id"))
		{
			sectionId = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("description"))
		{
			description = attributeValue;
		}
		else
		{
			LogWarning(FString::Printf(TEXT("Section中存在未知属性:%s：%s！"), *attributeName, *attributeValue));
		}
	}
	for (auto childNode : xmlNode->GetChildrenNodes())
	{
		FString nodeName = childNode->GetTag();
		if (nodeName == TEXT("Paragraph"))
		{
			UParagraph* paragraph = NewObject<UParagraph>();
			paragraph->Load(childNode);
			paragraphList.Add(paragraph);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("Section中存在未知节点:%s！"), *nodeName));
		}
	}
}