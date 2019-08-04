#include "ItemRecorder.h"
#include "../../Manager/LogManager.h"

void UItemRecorder::LoadRecorder(FXmlNode* xmlNode)
{
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("id"))
		{
			id = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("itemName"))
		{
			itemName = attributeValue;
		}
		else if (attributeName == TEXT("description"))
		{
			description = attributeValue;
		}
		else if (attributeName == TEXT("imagePath"))
		{
			imagePath = attributeValue;
		}
		else if (attributeName == TEXT("useItemExecuteActionString"))
		{
			useItemExecuteActionString = attributeValue;
		}
		else if (attributeName == TEXT("itemWorth"))
		{
			itemWorth = FCString::Atoi(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s配置中存在未知属性:%s：%s！"), *GetClass()->GetName().Left(GetClass()->GetName().Len() - 8), *attributeName, *attributeValue));
		}
	}
}

FString UItemRecorder::GetItemName()
{
	return itemName;
}

FString UItemRecorder::GetDescription()
{
	return description;
}

FString UItemRecorder::GetImagePath()
{
	return imagePath;
}

FString UItemRecorder::GetUseItemExecuteActionString()
{
	return useItemExecuteActionString;
}

int UItemRecorder::GetItemWorth()
{
	return itemWorth;
}
