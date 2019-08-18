#include "ActorInfoBase.h"
#include "../Action/ActionBase.h"
#include "../Skill/SkillBase.h"
#include "../Script/Paragraph.h"
#include "../Manager/LogManager.h"
#include "../Manager/HelpManager.h"
#include "../Manager/ScriptManager.h"
#include "../Config/SceneData.h"
#include "../Config/ActorSkillData.h"

void UActorInfoBase::Load(FXmlNode* xmlNode)
{
	//基础属性
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == "actorId")
		{
			actorId = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == "actorName")
		{
			actorName = attributeValue;
		}
		else if (attributeName == "description")
		{
			description = attributeValue;
		}
		else if (attributeName == "defaultPosition")
		{
			defaultPosition = UHelpManager::ConvertFStringToFVector(attributeValue);
		}
		else if (attributeName == "defaultRotation")
		{
			defaultRotation = UHelpManager::ConvertFStringToFRotator(attributeValue);
		}
		else if (attributeName == "headImagePath")
		{
			headImagePath = attributeValue;
		}
		else
		{
			LogWarning(FString::Printf(TEXT("演员Id:%d配置中存在未知属性:%s！"), actorId, *attributeName));
		}
	}

	for (auto childNode : xmlNode->GetChildrenNodes())
	{
		FString nodeName = childNode->GetTag();
		//模型
		if (nodeName == "Model")
		{
			for (auto item : childNode->GetAttributes())
			{
				if (item.GetTag() == "modelName")
				{
					modelName = item.GetValue();
				}
				else if (item.GetTag() == "modelRootPath")
				{
					modelRootPath = item.GetValue();
				}
			}
		}
		//属性
		else if (nodeName == "PropertyList")
		{
			propertyMap.Empty();
			for (auto propertyNode : childNode->GetChildrenNodes())
			{
				FPropertyBase propertyBase;
				FString propertyTag = propertyNode->GetTag();
				if (propertyTag == TEXT("Attack"))
				{
					propertyBase.propertyEnum = PropertyEnum::Attact;
				}
				else if (propertyTag == TEXT("Defense"))
				{
					propertyBase.propertyEnum = PropertyEnum::Defense;
				}
				else if (propertyTag == TEXT("Speed"))
				{
					propertyBase.propertyEnum = PropertyEnum::Speed;
				}
				else if (propertyTag == TEXT("Life"))
				{
					propertyBase.propertyEnum = PropertyEnum::Life;
				}
				else if (propertyTag == TEXT("Power"))
				{
					propertyBase.propertyEnum = PropertyEnum::Power;
				}
				else if (propertyTag == TEXT("WarningRange"))
				{
					propertyBase.propertyEnum = PropertyEnum::WarningRange;
				}
				else if (propertyTag == TEXT("Score"))
				{
					propertyBase.propertyEnum = PropertyEnum::Score;
				}
				else
				{
					LogWarning(FString::Printf(TEXT("演员Id:%d配置中存在未知属性:%s！"), actorId, *propertyTag));
				}
				propertyBase.propertyValue = FCString::Atof(*propertyNode->GetAttribute(TEXT("value")));
				propertyMap.Add(propertyTag, propertyBase);
			}
		}
		//技能
		else if (nodeName == "SkillMap")
		{
			skillMap.Empty();
			for (auto skillNode : childNode->GetChildrenNodes())
			{
				USkillBase* skill = NewObject<USkillBase>();
				skill->Load(skillNode);
				skillMap.Add(skill->GetSkillId(),skill);
			}
		}
		//交互列表
		else if (nodeName == "Interact")
		{
			interactParagraph = NewObject<UParagraph>();
			interactParagraph->Load(childNode);
		}
		//附近列表
		else if (nodeName == "Nearby")
		{
			nearbyParagraph = NewObject<UParagraph>();
			nearbyParagraph->Load(childNode);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("演员Id:%d配置中存在未知节点:%s！"), actorId, *nodeName));
		}
	}
}

void UActorInfoBase::CopyData(UActorInfoBase* actorInfo)
{
	actorId = actorInfo->actorId;
	actorName = actorInfo->actorName;
	description = actorInfo->description;
	modelName = actorInfo->modelName;
	modelRootPath = actorInfo->modelRootPath;
	defaultPosition = actorInfo->defaultPosition;
	defaultRotation = actorInfo->defaultRotation;
	headImagePath = actorInfo->headImagePath;
	propertyMap = actorInfo->propertyMap;
	skillMap = actorInfo->skillMap;
	interactParagraph = actorInfo->interactParagraph;
	nearbyParagraph = actorInfo->nearbyParagraph;
}

void UActorInfoBase::CoverData(USceneActorData* sceneActorData)
{
	if (sceneActorData->actorId == actorId)
	{
		defaultPosition = sceneActorData->position;
		defaultRotation = sceneActorData->rotation;
	}
	else
	{
		LogError(TEXT("使用FSaveActorInfo覆盖UActorInfoBase数据时actorId不同。"));
	}
}

void UActorInfoBase::CoverData(UActorSkillData* actorSkillData)
{
	skillMap.Empty();
	for (auto var : actorSkillData->GetSkillDataMap())
	{
		USkillBase* skill = NewObject<USkillBase>();
		
		skill->Load(&var.Value);
		skillMap.Add(var.Key, skill);
	}
}

void UActorInfoBase::SetActorEnum(ActorEnum newActorEnum)
{
	actorEnum = newActorEnum;
}

ActorEnum UActorInfoBase::GetActorEnum()
{
	return actorEnum;
}

int UActorInfoBase::GetActorId()
{
	return actorId;
}

void UActorInfoBase::SetActorName(FString newActorName)
{
	actorName = newActorName;
}

FString UActorInfoBase::GetActorName()
{
	return actorName;
}

FString UActorInfoBase::GetHeadImagePath()
{
	return headImagePath;
}

FString UActorInfoBase::GetModelName()
{
	return modelName;
}

FString UActorInfoBase::GetModelRootPath()
{
	return modelRootPath;
}

FVector UActorInfoBase::GetDefaultPosition()
{
	return defaultPosition;
}

FRotator UActorInfoBase::GetDefaultRotation()
{
	return defaultRotation;
}

float UActorInfoBase::GetPropertyValue(FString propertyName)
{
	if (propertyMap.Contains(propertyName))
	{
		return propertyMap[propertyName].propertyValue;
	}
	else
	{
		LogError(FString::Printf(TEXT("演员Id:%d没有此项属性:%s！"), actorId, *propertyName));
	}
	return 0;
}

TMap<FString, FPropertyBase> UActorInfoBase::GetPropertyMap()
{
	return propertyMap;
}

TMap<int, USkillBase*> UActorInfoBase::GetSkillMap()
{
	return skillMap;
}

UParagraph* UActorInfoBase::GetInteractParagraph()
{
	return interactParagraph;
}

UParagraph* UActorInfoBase::GetNearbyParagraph()
{
	return nearbyParagraph;
}
