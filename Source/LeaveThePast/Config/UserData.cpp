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
	FXmlFile* xmlFile = new FXmlFile(savePath);
	if (!xmlFile->IsValid())
	{
		LogError(FString::Printf(TEXT("存档文件加载失败：%s，使用初始存档。"), *savePath));
		SetInitData();
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
			gameTimeData.SetTime(timespan.GetHours(), timespan.GetMinutes(), timespan.GetSeconds());
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
					saveActorInfo.actorId = (FCString::Atoi(*idString));
				}
				FString positionString = itemNode->GetAttribute(TEXT("position"));
				if (!positionString.IsEmpty())
				{
					saveActorInfo.position = (UHelpManager::ConvertFStringToFVector(positionString));
				}
				FString rotationString = itemNode->GetAttribute(TEXT("rotation"));
				if (!rotationString.IsEmpty())
				{
					saveActorInfo.rotation = (UHelpManager::ConvertFStringToFRotator(rotationString));
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
				AddItem(id, number);
			}
		}
		//加载剧本
		if (xmlNode->GetTag() == TEXT("Script"))
		{
			chapterMap.Empty();
			for (FXmlNode* chapterNode : xmlNode->GetChildrenNodes())
			{
				FSaveChapterInfo chaterInfo;
				chaterInfo.name = chapterNode->GetAttribute(TEXT("name"));
				chaterInfo.state = FCString::Atoi(*chapterNode->GetAttribute(TEXT("state")));
				for (FXmlNode* sectionNode : chapterNode->GetChildrenNodes())
				{
					FSaveSectionInfo sectionInfo;
					sectionInfo.id = FCString::Atoi(*sectionNode->GetAttribute(TEXT("id")));
					sectionInfo.state = FCString::Atoi(*sectionNode->GetAttribute(TEXT("state")));
					for (FXmlNode* paragraphNode : sectionNode->GetChildrenNodes())
					{
						int paragraphId = FCString::Atoi(*paragraphNode->GetAttribute(TEXT("id")));
						int paragraphState = FCString::Atoi(*paragraphNode->GetAttribute(TEXT("state")));
						sectionInfo.paragraphMap.Add(paragraphId, paragraphState);
					}
					chaterInfo.sectionMap.Add(sectionInfo.id,sectionInfo);
				}
				chapterMap.Add(chaterInfo.name,chaterInfo);
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
	xmlContent.Append(TEXT("time=\"") + UHelpManager::ConvertToFString(gameTimeData.GetTimespan()) + TEXT("\" "));
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
		if (var.Value != 0)
		{
			xmlContent.Append(TEXT("\t\t<Item "));
			xmlContent.Append(TEXT("id=\"") + FString::FromInt(var.Key) + TEXT("\" "));
			xmlContent.Append(TEXT("number=\"") + FString::FromInt(var.Value) + TEXT("\" "));
			xmlContent.Append(TEXT("/>\n"));
		}
	}
	xmlContent.Append(TEXT("\t</ItemMap>\n"));
	//end 添加物品map
	//start 添加剧本信息
	xmlContent.Append(TEXT("\t<Script>\n"));
	for (auto chapterInfo : chapterMap)
	{
		xmlContent.Append(TEXT("\t\t<Chapter "));
		xmlContent.Append(TEXT("name=\"") + chapterInfo.Value.name + TEXT("\" "));
		xmlContent.Append(TEXT("state=\"") + FString::FromInt(chapterInfo.Value.state) + TEXT("\" "));
		xmlContent.Append(TEXT(">\n"));
		for (auto sectionInfo : chapterInfo.Value.sectionMap)
		{
			xmlContent.Append(TEXT("\t\t\t<Section "));
			xmlContent.Append(TEXT("id=\"") + FString::FromInt(sectionInfo.Value.id) + TEXT("\" "));
			xmlContent.Append(TEXT("state=\"") + FString::FromInt(sectionInfo.Value.state) + TEXT("\" "));
			xmlContent.Append(TEXT(">\n"));
			for (auto paragraphInfo : sectionInfo.Value.paragraphMap)
			{
				xmlContent.Append(TEXT("\t\t\t\t<Paragraph "));
				xmlContent.Append(TEXT("id=\"") + FString::FromInt(paragraphInfo.Key) + TEXT("\" "));
				xmlContent.Append(TEXT("state=\"") + FString::FromInt(paragraphInfo.Value) + TEXT("\" "));
				xmlContent.Append(TEXT("/>\n"));
			}
			xmlContent.Append(TEXT("\t\t\t</Section>\n"));
		}
		xmlContent.Append(TEXT("\t\t</Chapter>\n"));
	}
	xmlContent.Append(TEXT("\t</Script>\n"));
	//end 添加剧本信息
	xmlContent.Append(TEXT("</UserData>"));

	FXmlFile* xmlFile = new FXmlFile(xmlContent, EConstructMethod::ConstructFromBuffer);
	xmlFile->Save(savePath);
	xmlFile->Clear();
	delete xmlFile;
}

void UUserData::SetInitData()
{
	gameTimeData.SetTime(9, 0, 0);

	AddItem(10001, 50);
	AddItem(10002, 1);
	AddItem(10003, 1);
	AddItem(10004, 1);
	AddItem(10005, 1);
	AddItem(20001, 10);
	AddItem(20002, 3);
	AddItem(40004, 1);

	//AddControlActor(10001,FVector(3705.0, -3075.0, 570.0), FRotator(0, 0, 0));
}

FTimeData UUserData::GetGameTimeData()
{
	return gameTimeData;
}

void UUserData::SetGameTime(int hour, int minute, int second)
{
	gameTimeData.SetTime(hour, minute, second);
}

void UUserData::Tick(float secondTime)
{
	if (!isFixedTime)
	{
		gameTimeData.Tick(secondTime * gameAndRealTimeRate);
	}
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

void UUserData::AddControlActor(int actorInfoId, FVector position, FRotator rotation)
{
	for (auto saveActorInfo:canControlActorList)
	{
		if (saveActorInfo.actorId == actorInfoId)
		{
			LogError(FString::Printf(TEXT("在向存档中添加可控演员时重复infoId:%d"), actorInfoId));
			return;
		}

	}
	FSaveActorInfo saveActorInfo;
	saveActorInfo.actorId = actorInfoId;
	saveActorInfo.position = position;
	saveActorInfo.rotation = rotation;
	canControlActorList.Add(saveActorInfo);
}

void UUserData::RemoveControlActor(int actorInfoId)
{
	for (int i = 0;i<canControlActorList.Num();i++)
	{
		if (canControlActorList[i].actorId == actorInfoId)
		{
			canControlActorList.RemoveAt(i);
			return;
		}
	}
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

TMap<FString, FSaveChapterInfo> UUserData::GetChapterMap()
{
	return chapterMap;
}

