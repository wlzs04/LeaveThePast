#include "..\..\Public\Actor\ActorInfoBase.h"

void UActorInfoBase::Load(FXmlNode* xmlNode)
{
	//基础属性
	for (auto item : xmlNode->GetAttributes())
	{
		if (item.GetTag() == "actorId")
		{
			actorId = FCString::Atoi(*item.GetValue());
		}
		else if (item.GetTag() == "actorName")
		{
			actorName = item.GetValue();
		}
		else if (item.GetTag() == "description")
		{
			description = item.GetValue();
		}
		else if (item.GetTag() == "defaultPosition")
		{
			FString defaultPositionString = item.GetValue();
			TArray<FString> stringArray;
			defaultPositionString.ParseIntoArray(stringArray, TEXT(","));
			if (stringArray.Num() == 3)
			{
				defaultPosition.X = FCString::Atof(*stringArray[0]);
				defaultPosition.Y = FCString::Atof(*stringArray[1]);
				defaultPosition.Z = FCString::Atof(*stringArray[2]);
			}
		}
		else if (item.GetTag() == "defaultRotation")
		{
			FString defaultRotationString = item.GetValue();
			TArray<FString> stringArray;
			defaultRotationString.ParseIntoArray(stringArray, TEXT(","));
			if (stringArray.Num() == 3)
			{
				defaultRotation.Roll = FCString::Atof(*stringArray[0]);
				defaultRotation.Pitch = FCString::Atof(*stringArray[1]);
				defaultRotation.Yaw = FCString::Atof(*stringArray[2]);
			}
		}
		else if (item.GetTag() == "isPermanent")
		{
			isPermanent = item.GetValue().ToBool();
		}
		else
		{
			UE_LOG(LogLoad, Log, TEXT("演员Id:%d配置中存在未知属性:%s！"), actorId, *item.GetTag());
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
				UPropertyBase* propertyBase = nullptr;
				FString propertyName = propertyNode->GetTag();
				if (propertyName == TEXT("Attack"))
				{
					propertyBase = NewObject<UPropertyBase>();
				}
				else if (propertyName == TEXT("Defense"))
				{
					propertyBase = NewObject<UPropertyBase>();
				}
				else if (propertyNode->GetTag() == TEXT("Speed"))
				{
					propertyBase = NewObject<UPropertyBase>();
				}
				else if (propertyName == TEXT("Life"))
				{
					propertyBase = NewObject<UPropertyBase>();
				}
				else if (propertyName == TEXT("Power"))
				{
					propertyBase = NewObject<UPropertyBase>();
				}
				else
				{
					UE_LOG(LogLoad, Log, TEXT("演员Id:%d配置中存在未知属性:%s！"), actorId, *propertyName);
				}
				propertyBase->SetInfo(propertyNode->GetAttribute(TEXT("name")), propertyNode->GetAttribute(TEXT("value")));
				propertyMap.Add(propertyNode->GetTag(), propertyBase);
			}
		}
	}
}

int UActorInfoBase::GetActorId()
{
	return actorId;
}

bool UActorInfoBase::IsPermanent()
{
	return isPermanent;
}

FString UActorInfoBase::GetActorName()
{
	return actorName;
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

FString UActorInfoBase::GetPropertyValue(FString propertyName)
{
	if (propertyMap.Contains(propertyName))
	{
		return propertyMap[propertyName]->GetPropertyValue();
	}
	return TEXT("未找到");
}

TMap<FString, UPropertyBase*> UActorInfoBase::GetPropertyMap()
{
	return propertyMap;
}
