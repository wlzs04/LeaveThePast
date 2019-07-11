#include "SellItemRecorder.h"

void USellItemRecorder::LoadRecorder(FXmlNode* xmlNode)
{
	URecorderBase::LoadRecorder(xmlNode);

	itemId = FCString::Atoi(*xmlNode->GetAttribute(TEXT("itemId")));
	price = FCString::Atoi(*xmlNode->GetAttribute(TEXT("price")));
}

FString USellItemRecorder::GetRecordName()
{
	return TEXT("SellItem");
}

int USellItemRecorder::GetItemId()
{
	return itemId;
}

int USellItemRecorder::GetPrice()
{
	return price;
}