#include "KeySkillMapData.h"
#include "XmlParser/Public/XmlFile.h"
#include "../Manager/HelpManager.h"
#include "../Manager/LogManager.h"

void UKeySkillMapData::LoadFromXmlNode(FXmlNode* xmlNode)
{
	keySkillMap.Empty();
	for (FXmlNode* mapNode : xmlNode->GetChildrenNodes())
	{
		FKey key(*mapNode->GetAttribute(TEXT("key")));
		int skillId = FCString::Atoi(*mapNode->GetAttribute(TEXT("skillId")));
		keySkillMap.Add(key, skillId);
	}
}

int UKeySkillMapData::GetSkillIdByKey(FKey key)
{
	if (keySkillMap.Contains(key))
	{
		return keySkillMap[key];
	}
	return 0;
}
