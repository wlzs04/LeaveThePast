#include "StringRecorder.h"
#include "../../Manager/LogManager.h"

void UStringRecorder::LoadRecorder(FXmlNode* xmlNode)
{
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("id"))
		{
			id = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("value"))
		{
			value = attributeValue;
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s配置中存在未知属性:%s：%s！"), *GetClass()->GetName().Left(GetClass()->GetName().Len() - 8), *attributeName, *attributeValue));
		}
	}
}

FString UStringRecorder::GetValue()
{
	return value;
}
