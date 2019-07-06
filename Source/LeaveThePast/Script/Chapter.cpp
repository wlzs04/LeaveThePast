#include "Chapter.h"

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
		UE_LOG(LogLoad, Error, TEXT("Chapter文件加载失败：%s"), *chapterPath);
		return;
	}
	FXmlNode* rootNode = xmlFile->GetRootNode();
	for (FXmlAttribute attribute : rootNode->GetAttributes())
	{
		if (attribute.GetTag()==TEXT("name"))
		{
			chatperName = attribute.GetValue();
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
	UE_LOG(LogLoad, Log, TEXT("Chapter文件：%s加载完成！"), *chapterPath);
}

bool UChapter::GetIsCompleted()
{
	return isCompleted;
}

USection* UChapter::GetCurrentSection()
{
	return currentSection;
}

void UChapter::Start()
{
	for (auto section: sectionList)
	{
		if (!section->GetIsCompleted())
		{
			section->Start();
			currentSection = section;
			return;
		}
	}
	isCompleted = true;
}
