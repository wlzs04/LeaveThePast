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
		if (attribute.GetTag()==TEXT("name"))
		{
			chapterName = attribute.GetValue();
		}
		else if (attribute.GetTag() == TEXT("description"))
		{
			description = attribute.GetValue();
		}
	}
	for (auto childNode : rootNode->GetChildrenNodes())
	{
		USection* section = NewObject<USection>();
		section->Load(childNode);
		sectionList.Add(section);
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

void UChapter::Start(int sectionId, int paragrapgId)
{
	isCompleted = false;
	currentSection = sectionList[sectionId];
	currentSection->Start(paragrapgId);
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