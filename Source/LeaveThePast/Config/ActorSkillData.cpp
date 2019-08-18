#include "ActorSkillData.h"
#include "XmlParser/Public/XmlFile.h"
#include "../Manager/HelpManager.h"
#include "../Manager/LogManager.h"

void UActorSkillData::LoadFromXmlNode(FXmlNode* xmlNode)
{
	skillDataMap.Empty();
	for (FXmlNode* mapNode : xmlNode->GetChildrenNodes())
	{
		FSkillData skillData;
		for (auto attribute : mapNode->GetAttributes())
		{
			FString attributeName = attribute.GetTag();
			FString attributeValue = attribute.GetValue();
			if (attributeName == "skillId")
			{
				skillData.skillId = FCString::Atoi(*attributeValue);
			}
			else if (attributeName == "key")
			{
				skillData.key = FKey(*attributeValue);
			}
			else if (attributeName == "proficiency")
			{
				skillData.proficiency = FCString::Atoi(*attributeValue);
			}
			else
			{
				LogWarning(FString::Printf(TEXT("存档中技能存在未知属性:%s:%s！"), *attributeName,*attributeValue));
			}
		}
		skillDataMap.Add(skillData.skillId, skillData);
	}
}

FSkillData UActorSkillData::GetSkillDataById(int skillId)
{
	if (skillDataMap.Contains(skillId))
	{
		return skillDataMap[skillId];
	}
	return FSkillData();
}

FSkillData UActorSkillData::GetSkillDataByKey(FKey key)
{
	for (auto var : skillDataMap)
	{
		if (var.Value.key == key)
		{
			return var.Value;
		}
	}
	return FSkillData();
}

TMap<int, FSkillData> UActorSkillData::GetSkillDataMap()
{
	return skillDataMap;
}
