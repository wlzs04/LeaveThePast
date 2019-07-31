#include "ActorInfoBase.h"
#include "../Manager/LogManager.h"
#include "../Manager/HelpManager.h"
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
		else if (attributeName == "actorType")
		{
			actorType = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == "actorTypeValue")
		{
			actorTypeValue = attributeValue;
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
		//闲话列表
		if (nodeName == "ChatList")
		{
			for (auto chatNode : childNode->GetChildrenNodes())
			{
				FChat chat(chatNode->GetAttribute(TEXT("text")), chatNode->GetAttribute(TEXT("voicePath")));
				chatList.Add(chat);
			}
		}
		//模型
		else if (nodeName == "Model")
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
	actorType = actorInfo->actorType;
	actorTypeValue = actorInfo->actorTypeValue;
	description = actorInfo->description;
	modelName = actorInfo->modelName;
	modelRootPath = actorInfo->modelRootPath;
	defaultPosition = actorInfo->defaultPosition;
	defaultRotation = actorInfo->defaultRotation;
	headImagePath = actorInfo->headImagePath;
	propertyMap = actorInfo->propertyMap;
	chatList = actorInfo->chatList;
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

int UActorInfoBase::GetActorType()
{
	return actorType;
}
FString UActorInfoBase::GetActorTypeValue()
{
	return actorTypeValue;
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

FChat UActorInfoBase::GetRandomChat()
{
	if (chatList.Num()==0)
	{
		return FChat();
	}
	int index =FMath::RandRange(0, chatList.Num()-1);
	return chatList[index];
}
