#include "ActorInfoBase.h"
#include "../Manager/LogManager.h"
#include "../Manager/HelpManager.h"
#include "../Manager/ScriptManager.h"
#include "../Config/SceneData.h"

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
				else
				{
					LogWarning(FString::Printf(TEXT("演员Id:%d配置中存在未知属性:%s！"), actorId, *propertyTag));
				}
				propertyBase.propertyName = propertyNode->GetAttribute(TEXT("name"));
				propertyBase.propertyValue = FCString::Atof(*propertyNode->GetAttribute(TEXT("value")));
				propertyMap.Add(propertyTag, propertyBase);
			}
		}
		//交互列表
		else if (nodeName == "Interact")
		{
			UScriptManager* scriptManager = UScriptManager::GetInstance();
			for (auto actionNode : childNode->GetChildrenNodes())
			{
				FString actionName = actionNode->GetTag();
				UActionBase* actionBase = scriptManager->GetIegalActionByName(actionName);

				if (actionBase != nullptr)
				{
					UActionBase* actionBase2 = NewObject<UActionBase>((UObject*)GetTransientPackage(), actionBase->GetClass());
					actionBase2->Load(actionNode);
					interactedActionList.Add(actionBase2);
				}
				else
				{
					LogError(FString::Printf(TEXT("演员信息Id:%d交互列表中出现未知指令：%s"),actorId, *actionName));
				}
			}
		}
		//附近列表
		else if (nodeName == "Nearby")
		{
			UScriptManager* scriptManager = UScriptManager::GetInstance();
			for (auto actionNode : childNode->GetChildrenNodes())
			{
				FString actionName = actionNode->GetTag();
				UActionBase* actionBase = scriptManager->GetIegalActionByName(actionName);

				if (actionBase != nullptr)
				{
					UActionBase* actionBase2 = NewObject<UActionBase>((UObject*)GetTransientPackage(), actionBase->GetClass());
					actionBase2->Load(actionNode);
					nearbyActionList.Add(actionBase2);
				}
				else
				{
					LogError(FString::Printf(TEXT("演员信息Id:%d附近列表中出现未知指令：%s"), actorId, *actionName));
				}
			}
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
	interactedActionList = actorInfo->interactedActionList;
	nearbyActionList = actorInfo->nearbyActionList;
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

TArray<UActionBase*> UActorInfoBase::GetInteractedActionList()
{
	return interactedActionList;
}

TArray<UActionBase*> UActorInfoBase::GetNearbyActionList()
{
	return nearbyActionList;
}
