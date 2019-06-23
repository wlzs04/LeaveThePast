#include "..\..\Public\Actor\ActorInfoBase.h"

void UActorInfoBase::Load(FXmlNode* xmlNode)
{
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
		else if (item.GetTag() == "modelName")
		{
			modelName = item.GetValue();
		}
		else if (item.GetTag() == "modelRootPath")
		{
			modelRootPath = item.GetValue();
		}
		else if (item.GetTag() == "defaultPosition")
		{
			FString defaultPositionString = item.GetValue();
			TArray<FString> stringArray;
			defaultPositionString.ParseIntoArray(stringArray, TEXT(","));
			if (stringArray.Num() == 3)
			{
				defaultPosition.X = FCString::Atoi(*stringArray[0]);
				defaultPosition.Y = FCString::Atoi(*stringArray[1]);
				defaultPosition.Z = FCString::Atoi(*stringArray[2]);
			}
		}
		else if (item.GetTag() == "defaultRotation")
		{
			FString defaultRotationString = item.GetValue();
			TArray<FString> stringArray;
			defaultRotationString.ParseIntoArray(stringArray, TEXT(","));
			if (stringArray.Num() == 3)
			{
				defaultRotation.Roll = FCString::Atoi(*stringArray[0]);
				defaultRotation.Pitch = FCString::Atoi(*stringArray[1]);
				defaultRotation.Yaw = FCString::Atoi(*stringArray[2]);
			}
		}
		else if (item.GetTag() == "isPermanent")
		{
			isPermanent = item.GetValue().ToBool();
		}
	}

	for (auto childNode : xmlNode->GetChildrenNodes())
	{
		if (childNode->GetTag() == "ChatList")
		{
			for (auto chatNode : childNode->GetChildrenNodes())
			{
				FChat chat(chatNode->GetAttribute(TEXT("text")), chatNode->GetAttribute(TEXT("voicePath")));
				chatList.Add(chat);
			}
		}
		if (childNode->GetTag() == "Model")
		{
			for (auto item : childNode->GetAttributes())
			{
				if (item.GetTag() == "modelName")
				{
					modelName = item.GetValue();
				}
				if (item.GetTag() == "modelRootPath")
				{
					modelRootPath = item.GetValue();
				}
			}
		}
		if (childNode->GetTag() == "PropertyList")
		{
			
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