#include "ItemRecorder.h"

void UItemRecorder::LoadRecorder(FXmlNode* xmlNode)
{
	URecorderBase::LoadRecorder(xmlNode);
	
	itemName = xmlNode->GetAttribute(TEXT("itemName"));
	FString itemTypeString = xmlNode->GetAttribute(TEXT("itemType"));
	if (!itemTypeString.IsEmpty())
	{
		itemType = FCString::Atoi(*itemTypeString);
	}
	description = xmlNode->GetAttribute(TEXT("description"));
	imagePath = xmlNode->GetAttribute(TEXT("imagePath"));
}

FString UItemRecorder::GetItemName()
{
	return itemName;
}

int UItemRecorder::GetTtemType()
{
	return itemType;
}

FString UItemRecorder::GetDescription()
{
	return description;
}

FString UItemRecorder::GetImagePath()
{
	return imagePath;
}
