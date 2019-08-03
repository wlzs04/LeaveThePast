#include "Section.h"
#include "Paragraph.h"
#include "../Manager/LogManager.h"
#include "XmlParser/Public/XmlFile.h"

void USection::Update()
{
	/*if (!isCompleted && currentParagraph != nullptr)
	{
		if (!currentParagraph->GetIsCompleted())
		{
			currentParagraph->Update();
		}
		else
		{
			currentParagraph = nullptr;
			for (auto paragraph : paragraphList)
			{
				if (!paragraph->GetIsCompleted())
				{
					return;
				}
			}
			isCompleted = true;
		}
	}*/
}

//bool USection::GetIsCompleted()
//{
//	return isCompleted;
//}

int USection::GetSectionId()
{
	return sectionId;
}

TArray<UParagraph*> USection::GetParagraphList()
{
	return paragraphList;
}

//UParagraph* USection::GetCurrentParagraph()
//{
//	return currentParagraph;
//}

//bool USection::Start(int paragrapgId)
//{
//	if ((paragrapgId >= 0) && (paragrapgId < paragraphList.Num()))
//	{
//		isCompleted = false;
//		currentParagraph = paragraphList[paragrapgId];
//		return currentParagraph->Start();
//	}
//	else
//	{
//		LogError(FString::Printf(TEXT("Section%d中没有Paragrapg%d。"), sectionId, paragrapgId));
//	}
//	return false;
//}

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