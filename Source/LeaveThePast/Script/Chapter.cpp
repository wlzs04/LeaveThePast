#include "Chapter.h"
#include "Section.h"
#include "XmlParser/Public/XmlFile.h"
#include "../Manager/LogManager.h"

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

TArray<USection*> UChapter::GetSectionList()
{
	return sectionList;
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