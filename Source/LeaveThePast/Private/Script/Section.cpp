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
			isCompleted = true;
		}
	}
}

bool USection::GetIsCompleted()
{
	return isCompleted;
}

void USection::Start()
{
	if (paragraphList.Num() > 0)
	{
		paragraphList[0]->Start();
		currentParagraph = paragraphList[0];
	}
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


