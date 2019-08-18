#include "SkillBase.h"
#include "XmlParser/Public/XmlFile.h"
#include "../Manager/LogManager.h"
#include "../Manager/ConfigManager.h"
#include "../Manager/UIManager.h"
#include "../Config/Recorder/SkillRecorder.h"
#include "../Config/ActorSkillData.h"

void USkillBase::Load(FXmlNode* xmlNode)
{
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("id"))
		{
			skillId = FCString::Atoi(*attributeValue);
			skillRecorder = (USkillRecorder*)UConfigManager::GetInstance()->GetConfigByNameId(USkillRecorder::StaticClass(), TEXT(""), skillId);
			if (skillRecorder == nullptr)
			{
				LogError(FString::Printf(TEXT("演员技能列表中Id:%d在技能表中不存在！"), skillId));
			}
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

void USkillBase::Load(FSkillData* skillData)
{
	skillId = skillData->skillId;
	skillRecorder = (USkillRecorder*)UConfigManager::GetInstance()->GetConfigByNameId(USkillRecorder::StaticClass(), TEXT(""), skillId);
	proficiency = skillData->proficiency;
	key = skillData->key;
}

void USkillBase::Use()
{
	if (skillRecorder == nullptr)
	{
		return;
	}
	UUIManager::GetInstance()->AddMessageTip(FString::Printf(TEXT("使用技能：%s"), *skillRecorder->GetSkillName()));
}

int USkillBase::GetSkillId()
{
	return skillId;
}

int USkillBase::GetProficiency()
{
	return proficiency;
}

void USkillBase::SetKey(FKey newKey)
{
	key = newKey;
}

FKey USkillBase::GetKey()
{
	return key;
}

FString USkillBase::GetKeyString()
{
	return key.ToString();
}

USkillRecorder* USkillBase::GetSkillRecorder()
{
	return skillRecorder;
}
