#include "../../Public/Script/Section.h"

void USection::Update()
{
	if (!isCompleted && currentParagraph != nullptr)
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
	}
}

bool USection::GetIsCompleted()
{
	return isCompleted;
}

UParagraph* USection::GetCurrentParagraph()
{
	return currentParagraph;
}

void USection::Start()
{
	for (auto paragraph : paragraphList)
	{
		if (!paragraph->GetIsCompleted())
		{
			paragraph->Start();
			currentParagraph = paragraph;
			return;
		}
	}
	isCompleted = true;
}

void USection::Load(FXmlNode* xmlNode)
{
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		if (attribute.GetTag() == TEXT("name"))
		{
			sectionName = attribute.GetValue();
		}
		else if (attribute.GetTag() == TEXT("description"))
		{
			description = attribute.GetValue();
		}
	}
	for (auto childNode : xmlNode->GetChildrenNodes())
	{
		UParagraph* paragraph = NewObject<UParagraph>();
		paragraph->Load(childNode);
		paragraphList.Add(paragraph);
	}
}


