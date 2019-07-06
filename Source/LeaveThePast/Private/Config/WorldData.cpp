#include "WorldData.h"
#include "Paths.h"

UWorldData::UWorldData() :UObject()
{
	savePath = FPaths::ProjectContentDir() + TEXT("GameContent/Artres/Config/World.xml");
}

void UWorldData::Load()
{
	FXmlFile* xmlFile = new FXmlFile(savePath);
	if (!xmlFile->IsValid())
	{
		//UE_LOG(LogLoad, Error, TEXT("存档文件加载失败：%s"), *savePath);
		return;
	}

	FXmlNode* rootNode = xmlFile->GetRootNode();

	sceneDataList.Empty();
	for (auto var : rootNode->GetChildrenNodes())
	{
		USceneData* childSceneData = NewObject<USceneData>();
		childSceneData->Load(var);
		sceneDataList.Add(childSceneData);
	}
}
