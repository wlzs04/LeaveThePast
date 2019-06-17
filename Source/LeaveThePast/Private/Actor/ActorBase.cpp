#include "ActorBase.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AActorBase::AActorBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AActorBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActorBase::Load(FXmlNode* xmlNode)
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
		else if (item.GetTag() == "modelPath")
		{
			modelPath = item.GetValue();
		}
		else if (item.GetTag() == "defaultPosition")
		{
			modelPath = item.GetValue();
		}
		else if (item.GetTag() == "defaultRotation")
		{
			modelPath = item.GetValue();
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
	}
}

void AActorBase::StartPerform()
{
	FString modelName = TEXT("SkeletalMesh'/Game/");
	modelName += modelPath;
	modelName += TEXT("'");
	USkeletalMesh* newMesh = LoadObject<USkeletalMesh>(NULL, modelName.GetCharArray().GetData());
	GetMesh()->SetSkeletalMesh(newMesh);
}

int AActorBase::GetActorId()
{
	return actorId;
}
