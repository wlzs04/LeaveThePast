#include "Section.h"

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

int USection::GetSectionId()
{
	return sectionId;
}

UParagraph* USection::GetCurrentParagraph()
{
	return currentParagraph;
}

void USection::Start(int paragrapgId)
{
	isCompleted = false;
	currentParagraph = paragraphList[paragrapgId];
	currentParagraph->Start();
}

void USection::Load(FXmlNode* xmlNode)
{
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		if (attribute.GetTag() == TEXT("name"))
		{
			sectionName = attribute.GetValue();
		}
		else if (attribute.GetTag() == TEXT("id"))
		{
			sectionId = FCString::Atoi(*attribute.GetValue());
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