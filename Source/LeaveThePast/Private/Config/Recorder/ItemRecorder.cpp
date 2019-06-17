#include "../../../Public/Config/Recorder/ItemRecorder.h"

void UItemRecorder::LoadRecorder(FXmlNode* xmlNode)
{
	URecorderBase::LoadRecorder(xmlNode);

	itemName = xmlNode->GetAttribute(TEXT("itemName"));
	FString itemTypeString = xmlNode->GetAttribute(TEXT("itemType"));
	if (!itemTypeString.IsEmpty())
	{
		itemType = id = FCString::Atoi(*itemTypeString);
	}
	descript = xmlNode->GetAttribute(TEXT("descript"));
}

FString UItemRecorder::GetRecordName()
{
	return TEXT("Item");
}

FString UItemRecorder::GetItemName()
{
	return itemName;
}

int UItemRecorder::GetTtemType()
{
	return itemType;
}

FString UItemRecorder::GetDescript()
{
	return descript;
}
