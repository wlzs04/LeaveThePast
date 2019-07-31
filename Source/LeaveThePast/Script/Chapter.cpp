#include "Chapter.h"
#include "Section.h"
#include "XmlParser/Public/XmlFile.h"
#include "../Manager/LogManager.h"

void UChapter::Update()
{
	if (!isCompleted && currentSection != nullptr)
	{
		if (currentSection->GetCurrentParagraph())
		{
			currentSection->Update();
		}
		else
		{
			currentSection = nullptr;
			for (auto section : sectionList)
			{
				if (!section->GetIsCompleted())
				{
					return;
				}
			}
			isCompleted = true;
		}
	}
}

void UChapter::Load(FString newChapterPath)
{
	chapterPath = newChapterPath;
	FXmlFile* xmlFile = new FXmlFile(chapterPath);
	if (!xmlFile->IsValid())
	{
		LogError(FString::Printf(TEXT("Chapter文件加载失败：%s"), *chapterPath));
		return;
	}
	FXmlNode* rootNode = xmlFile->GetRootNode();
	for (FXmlAttribute attribute : rootNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName ==TEXT("name"))
		{
			chapterName = attributeValue;
		}
		else if (attributeName == TEXT("description"))
		{
			description = attributeValue;
		}
		else
		{
			LogWarning(FString::Printf(TEXT("Chapter路径：%s中存在未知属性:%s：%s！"), *chapterPath, *attributeName, *attributeValue));
		}
	}
	for (auto childNode : rootNode->GetChildrenNodes())
	{
		FString nodeName = childNode->GetTag();
		if (nodeName == TEXT("Section"))
		{
			USection* section = NewObject<USection>();
			section->Load(childNode);
			sectionList.Add(section);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("Chapter中存在未知节点:%s！"), *nodeName));
		}
	}
	xmlFile->Clear();
	delete xmlFile;
	LogNormal(FString::Printf(TEXT("Chapter文件：%s加载完成"), *chapterPath));
}

bool UChapter::GetIsCompleted()
{
	return isCompleted;
}

USection* UChapter::GetCurrentSection()
{
	return currentSection;
}

bool UChapter::Start(int sectionId, int paragrapgId)
{
	if ((sectionId >= 0) && (sectionId < sectionList.Num()))
	{
		isCompleted = false;
		currentSection = sectionList[sectionId];
		return currentSection->Start(paragrapgId);
	}
	else
	{
		LogError(FString::Printf(TEXT("Chapter%s中没有Section%d。"), *chapterIndexName,sectionId));
	}
	return false;
}

FString UChapter::GetChapterName()
{
	return chapterName;
}

void UChapter::SetChapterIndexName(FString newChapterIndexName)
{
	chapterIndexName = newChapterIndexName;
}

FString UChapter::GetChapterIndexName()
{
	return chapterIndexName;
}

FString UChapter::GetChapterDescription()
{
	return description;
}