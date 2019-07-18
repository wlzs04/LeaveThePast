#include "UserData.h"
#include "../Manager/MainGameManager.h"
#include "../Manager/HelpManager.h"
#include "Paths.h"
#include "XmlParser/Public/XmlFile.h"
#include "Engine/World.h"

UUserData::UUserData() :UObject()
{
	savePath = FPaths::ProjectContentDir() + TEXT("GameContent/Artres/Config/UserData.xml");
}

void UUserData::Load()
{
	gameTimeData = NewObject<UTimeData>(this);
	FXmlFile* xmlFile = new FXmlFile(savePath);
	if (!xmlFile->IsValid())
	{
		LogError(FString::Printf(TEXT("存档文件加载失败：%s"), *savePath));
		return;
	}

	FXmlNode* rootNode = xmlFile->GetRootNode();
	int hour = 6;
	int minute = 0;
	int second = 0;
	//加载基础属性
	for (auto attribute : rootNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("time"))
		{
			FTimespan timespan = UHelpManager::ConvertFStringToFTimespan(attributeValue);
			gameTimeData->SetTime(timespan.GetHours(), timespan.GetMinutes(), timespan.GetSeconds());
		}
		else if (attributeName == TEXT("isFixedTime"))
		{
			isFixedTime = attributeValue.ToBool();
		}
		else if (attributeName == TEXT("gameAndRealTimeRate"))
		{
			gameAndRealTimeRate = FCString::Atof(*attributeValue);
		}
		else if (attributeName == TEXT("sceneId"))
		{
			sceneId = FCString::Atoi(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("角色存档中存在未知属性：%s:%s"), *attributeName, *attributeValue));
		}
	}
	
	for (FXmlNode* xmlNode : rootNode->GetChildrenNodes())
	{
		//加载可控演员列表
		if (xmlNode->GetTag() == TEXT("CanControlActorList"))
		{
			canControlActorList.Empty();
			for (FXmlNode* itemNode : xmlNode->GetChildrenNodes())
			{
				FSaveActorInfo saveActorInfo;
				int actorId = 0;
				int number = 0;
				FString idString = itemNode->GetAttribute(TEXT("id"));
				if (!idString.IsEmpty())
				{
					saveActorInfo.SetActorId(FCString::Atoi(*idString));
				}
				FString positionString = itemNode->GetAttribute(TEXT("position"));
				if (!positionString.IsEmpty())
				{
					saveActorInfo.SetPosition(UHelpManager::ConvertFStringToFVector(positionString));
				}
				FString rotationString = itemNode->GetAttribute(TEXT("rotation"));
				if (!rotationString.IsEmpty())
				{
					saveActorInfo.SetRotation(UHelpManager::ConvertFStringToFRotator(rotationString));
				}
				canControlActorList.Add(saveActorInfo);
			}
		}
		//加载物品
		if (xmlNode->GetTag() == TEXT("ItemMap"))
		{
			itemMap.Empty();
			for (FXmlNode* itemNode : xmlNode->GetChildrenNodes())
			{
				int id = 0;
				int number = 0;
				FString idString = itemNode->GetAttribute(TEXT("id"));
				if (!idString.IsEmpty())
				{
					id = FCString::Atoi(*idString);
				}
				FString numberString = itemNode->GetAttribute(TEXT("number"));
				if (!numberString.IsEmpty())
				{
					number = FCString::Atoi(*numberString);
				}
				itemMap.Add(id, number);
			}
		}
	}

	xmlFile->Clear();
	delete xmlFile;
	LogNormal(FString::Printf(TEXT("Save文件：%s加载完成！"), *savePath));
}

void UUserData::Save()
{
	UMainGameManager* gameManager = Cast<UMainGameManager>(GetWorld()->GetGameInstance());
	ADirectorActor* directorActor = Cast<ADirectorActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	FString xmlContent = TEXT("<UserData ");
	//start 添加基础信息
	xmlContent.Append(TEXT("time=\"") + UHelpManager::ConvertToFString(gameTimeData->GetTimespan()) + TEXT("\" "));
	FString isFixedTimeString = (isFixedTime ? TEXT("true") : TEXT("false"));
	xmlContent.Append(TEXT("isFixedTime=\"") + isFixedTimeString + TEXT("\" "));
	xmlContent.Append(TEXT("gameAndRealTimeRate=\"") + FString::SanitizeFloat(gameAndRealTimeRate) + TEXT("\" "));
	xmlContent.Append(TEXT("sceneId=\"") + FString::FromInt(sceneId) + TEXT("\" "));
	//end 添加基础信息
	xmlContent.Append(TEXT(">\n"));
	//start 添加可控演员列表
	xmlContent.Append(TEXT("\t<CanControlActorList>\n"));
	for (AActorBase* actor : directorActor->GetCanControlActorList())
	{
		xmlContent.Append(TEXT("\t\t<Actor "));
		xmlContent.Append(TEXT("id=\"") + FString::FromInt(actor->GetActorInfo()->GetActorId()) + TEXT("\" "));
		xmlContent.Append(TEXT("position=\"") + UHelpManager::ConvertToFString(actor->GetActorLocation()) + TEXT("\" "));
		xmlContent.Append(TEXT("rotation=\"") + UHelpManager::ConvertToFString(actor->GetActorRotation()) + TEXT("\" "));
		xmlContent.Append(TEXT("/>\n"));
	}
	xmlContent.Append(TEXT("\t</CanControlActorList>\n"));
	//end 添加可控演员列表
	//start 添加物品map
	xmlContent.Append(TEXT("\t<ItemMap>\n"));
	for (auto var : itemMap)
	{
		xmlContent.Append(TEXT("\t\t<Item "));
		xmlContent.Append(TEXT("id=\"") + FString::FromInt(var.Key) + TEXT("\" "));
		xmlContent.Append(TEXT("number=\"") + FString::FromInt(var.Value) + TEXT("\" "));
		xmlContent.Append(TEXT("/>\n"));
	}
	xmlContent.Append(TEXT("\t</ItemMap>\n"));
	//end 添加物品map
	xmlContent.Append(TEXT("</UserData>"));

	FXmlFile* xmlFile = new FXmlFile(xmlContent, EConstructMethod::ConstructFromBuffer);
	xmlFile->Save(savePath);
	xmlFile->Clear();
	delete xmlFile;
}

UTimeData* UUserData::GetGameTimeData()
{
	return gameTimeData;
}

void UUserData::SetIsFixedTime(bool newIsFixedTime)
{
	isFixedTime = newIsFixedTime;
}

bool UUserData::GetIsFixedTime()
{
	return isFixedTime;
}

void UUserData::SetGameAndRealTimeRate(float newGameAndRealTimeRate)
{
	gameAndRealTimeRate = newGameAndRealTimeRate;
}

float UUserData::GetGameAndRealTimeRate()
{
	return gameAndRealTimeRate;
}

void UUserData::SetSceneId(int newSceneId)
{
	sceneId = newSceneId;
}

int UUserData::GetSceneId()
{
	return sceneId;
}

TArray<FSaveActorInfo> UUserData::GetCanControlActorList()
{
	return canControlActorList;
}

TMap<int, int> UUserData::GetItemMap()
{
	return itemMap;
}

int UUserData::GetItemNumberById(int itemId)
{
	if (itemMap.Contains(itemId))
	{
		return itemMap[itemId];
	}
	else
	{
		return 0;
	}
}

void UUserData::AddItem(int itemId, int number)
{
	if (itemMap.Contains(itemId))
	{
		itemMap[itemId] = itemMap[itemId] + number;
	}
	else
	{
		itemMap.Add(itemId, number);
	}
}

int UUserData::ReduceItem(int itemId, int number)
{
	int itemNumber = GetItemNumberById(itemId);
	if (itemNumber >= number)
	{
		SetItemNumber(itemId, itemNumber - number);
		return number;
	}
	else
	{
		SetItemNumber(itemId, 0);
		return itemNumber;
	}
}

void UUserData::SetItemNumber(int itemId, int number)
{
	if (itemMap.Contains(itemId))
	{
		itemMap[itemId] =  number;
	}
	else
	{
		itemMap.Add(itemId, number);
	}
}

int UUserData::GetMoney()
{
	TArray<int> itemList;
	itemMap.GetKeys(itemList);
	float totalMoney = 0;
	for (int i = 0; i<itemList.Num(); i++)
	{
		int itemId = itemList[i];
		int itemNumber = itemMap[itemId];
		if (itemId == 10001)
		{
			totalMoney += 1 * itemNumber;
		}
		else if(itemId == 10006)
		{
			totalMoney += 1000 * itemNumber;
		}
	}
	return totalMoney;
}

void UUserData::ReduceMoney(int money)
{
	int needReduceMoney = money;
	float totalMoney = 0;
	ReduceItem(10001, money);
}

