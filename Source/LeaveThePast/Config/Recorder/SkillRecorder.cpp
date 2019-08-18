#include "SkillRecorder.h"
#include "../../Manager/LogManager.h"
#include "EngineUtils.h"

void USkillRecorder::LoadRecorder(FXmlNode* xmlNode)
{
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("id"))
		{
			id = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("name"))
		{
			skillName = attributeValue;
		}
		else if (attributeName == TEXT("skillEnum"))
		{
			UEnum* skillEnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("SkillEnum"), true);
			skillEnum = (SkillEnum)skillEnumPtr->GetValueByNameString(attributeValue);
		}
		else if (attributeName == TEXT("description"))
		{
			description = attributeValue;
		}
		else if (attributeName == TEXT("iconPath"))
		{
			iconPath = attributeValue;
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s配置中存在未知属性:%s：%s！"), *GetClass()->GetName().Left(GetClass()->GetName().Len() - 8), *attributeName, *attributeValue));
		}
	}
}

FString USkillRecorder::GetSkillName()
{
	return skillName;
}

FString USkillRecorder::GetDescription()
{
	return description;
}

SkillEnum USkillRecorder::GetSkillEnum()
{
	return skillEnum;
}

FString USkillRecorder::GetIconPath()
{
	return iconPath;
}
