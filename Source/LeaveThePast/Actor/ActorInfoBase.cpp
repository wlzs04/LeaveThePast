#include "ActorInfoBase.h"
#include "../Manager/LogManager.h"
#include "../Manager/HelpManager.h"

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
		//闲话列表
		if (childNode->GetTag() == "ChatList")
		{
			for (auto chatNode : childNode->GetChildrenNodes())
			{
				FChat chat(chatNode->GetAttribute(TEXT("text")), chatNode->GetAttribute(TEXT("voicePath")));
				chatList.Add(chat);
			}
		}
		//模型
		if (childNode->GetTag() == "Model")
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
		if (childNode->GetTag() == "PropertyList")
		{
			for (auto propertyNode : childNode->GetChildrenNodes())
			{
				FPropertyBase propertyBase;
				FString propertyName = propertyNode->GetTag();
				if (propertyName == TEXT("Attack"))
				{
					propertyBase.propertyEnum = PropertyEnum::Attact;
				}
				else if (propertyName == TEXT("Defense"))
				{
					propertyBase.propertyEnum = PropertyEnum::Defense;
				}
				else if (propertyNode->GetTag() == TEXT("Speed"))
				{
					propertyBase.propertyEnum = PropertyEnum::Speed;
				}
				else if (propertyName == TEXT("Life"))
				{
					propertyBase.propertyEnum = PropertyEnum::Life;
				}
				else if (propertyName == TEXT("Power"))
				{
					propertyBase.propertyEnum = PropertyEnum::Power;
				}
				else
				{
					LogWarning(FString::Printf(TEXT("演员Id:%d配置中存在未知属性:%s！"), actorId, *propertyName));
				}
				propertyBase.propertyName = propertyName;
				propertyBase.propertyValue = FCString::Atof(*propertyNode->GetAttribute(TEXT("value")));
				propertyMap.Add(propertyName, propertyBase);
			}
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

void UActorInfoBase::CoverData(FSceneActorInfo sceneActorInfo)
{
	if (sceneActorInfo.actorId == actorId)
	{
		if (sceneActorInfo.needReplaceActorName)
		{
			actorName = sceneActorInfo.actorName;
		}
		if (sceneActorInfo.needReplaceDefaultPosition)
		{
			defaultPosition = sceneActorInfo.defaultPosition;
		}
		if (sceneActorInfo.needReplaceDefaultRotation)
		{
			defaultRotation = sceneActorInfo.defaultRotation;
		}
	}
	else
	{
		LogError(TEXT("使用FSceneActorInfo覆盖UActorInfoBase数据时actorId不同。"));
	}
}

int UActorInfoBase::GetActorId()
{
	return actorId;
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
