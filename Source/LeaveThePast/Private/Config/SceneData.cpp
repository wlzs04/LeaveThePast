#include "SceneData.h"
#include "Paths.h"

USceneData::USceneData() :UObject()
{
}

void USceneData::Load(FXmlNode* xmlNode)
{
	FString idString = xmlNode->GetAttribute(TEXT("id"));
	id = FCString::Atoi(*idString);
	sceneName = xmlNode->GetAttribute(TEXT("sceneName"));

	FString rangeXString = xmlNode->GetAttribute(TEXT("rangeX"));
	TArray<FString> tempStringArray;
	rangeXString.ParseIntoArray(tempStringArray,TEXT(","));
	rangeX = FVector2D(FCString::Atof(*tempStringArray[0]), FCString::Atof(*tempStringArray[1]));

	sceneDataList.Empty();
	for(auto var : xmlNode->GetChildrenNodes())
	{
		USceneData* childSceneData = NewObject<USceneData>();
		childSceneData->Load(var);
		sceneDataList.Add(childSceneData);
	}
}

int USceneData::GetId()
{
	return id;
}

FString USceneData::GetSceneName()
{
	return sceneName;
}

FVector2D USceneData::GetRangeX()
{
	return rangeX;
}

TArray<USceneData*> USceneData::GetSceneDataList()
{
	return sceneDataList;
}
