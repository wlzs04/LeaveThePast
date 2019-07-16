#include "UserData.h"
#include "../Manager/MainGameManager.h"
#include "Paths.h"
#include "XmlParser/Public/XmlFile.h"
#include "Engine/World.h"

UUserData::UUserData() :UObject()
{
	savePath = FPaths::ProjectContentDir() + TEXT("GameContent/Artres/Config/UserData.xml");
}

void UUserData::Save()
{
	UMainGameManager* gameManager = Cast<UMainGameManager>(GetWorld()->GetGameInstance());
	UTimeData* gameDuringTime = gameManager->GetGameDuringTime();
	hour = gameDuringTime->GetHours();
	minute = gameDuringTime->GetMinutes();
	second = gameDuringTime->GetSeconds();
	FString xmlContent = TEXT("<UserData ");
	//start 添加基础信息
	xmlContent.Append(TEXT("hour=\"") + FString::FromInt(hour) + TEXT("\" "));
	xmlContent.Append(TEXT("minute=\"") + FString::FromInt(minute) + TEXT("\" "));
	xmlContent.Append(TEXT("second=\"") + FString::FromInt(second) + TEXT("\" "));
	FString isFixedTimeString = (isFixedTime ? TEXT("true") : TEXT("false"));
	xmlContent.Append(TEXT("isFixedTime=\"") + isFixedTimeString + TEXT("\" "));
	xmlContent.Append(TEXT("gameAndRealTimeRate=\"") + FString::SanitizeFloat(gameAndRealTimeRate) + TEXT("\" "));
	//end 添加基础信息
	xmlContent.Append(TEXT(">\n"));
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

int UUserData::GetHour()
{
	return hour;
}

int UUserData::GetMinute()
{
	return minute;
}

int UUserData::GetSecond()
{
	return second;
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

void UUserData::Load()
{
	FXmlFile* xmlFile = new FXmlFile(savePath);
	if (!xmlFile->IsValid())
	{
		LogError(FString::Printf(TEXT("存档文件加载失败：%s"), *savePath));
		return;
	}

	FXmlNode* rootNode = xmlFile->GetRootNode();

	//加载基础属性
	for (auto attribute : rootNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("hour"))
		{
			hour = FCString::Atoi(*attributeValue);
		}
		else if(attributeName == TEXT("minute"))
		{
			minute = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("second"))
		{
			second = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("isFixedTime"))
		{
			isFixedTime = attributeValue.ToBool();
		}
		else if (attributeName == TEXT("gameAndRealTimeRate"))
		{
			gameAndRealTimeRate = FCString::Atof(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("角色存档中存在未知属性：%s:%s"), *attributeName, *attributeValue));
		}
	}
	{
		for (FXmlNode* xmlNode : rootNode->GetChildrenNodes())
		{
			//加载物品
			if (xmlNode->GetTag() == TEXT("ItemMap"))
			{
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
	}

	xmlFile->Clear();
	delete xmlFile;
	LogNormal(FString::Printf(TEXT("Save文件：%s加载完成！"), *savePath));
}
