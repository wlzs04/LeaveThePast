#include "SkillBase.h"
#include "XmlParser/Public/XmlFile.h"
#include "../Manager/LogManager.h"

void USkillBase::Load(FXmlNode* xmlNode)
{
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("id"))
		{
			skillId = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("proficiency"))
		{
			proficiency = FCString::Atoi(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("演员技能列表中存在未知属性:%s：%s！"),*attributeName, *attributeValue));
		}
	}
}

int USkillBase::GetSkillId()
{
	return skillId;
}

int USkillBase::GetProficiency()
{
	return proficiency;
}
