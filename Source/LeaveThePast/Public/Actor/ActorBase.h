#pragma once

#include "CoreMinimal.h"
#include "XmlParser/Public/XmlFile.h"
#include "GameFramework/Character.h"
#include "ActorBase.generated.h"

USTRUCT()
struct FChat
{
	GENERATED_USTRUCT_BODY()

	FString text;
	FString voicePath;

	FChat()
	{
		text = TEXT("无");
		voicePath = TEXT("");
	}

	FChat(FString newText, FString newVoicePath)
	{
		text = newText;
		voicePath = newVoicePath;
	}
};

UCLASS()
class LEAVETHEPAST_API AActorBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AActorBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Load(FXmlNode* xmlNode);

	//开始表演
	UFUNCTION(BlueprintCallable)
	virtual void StartPerform();

	int GetActorId();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int actorId = 0;//演员的Id
	FString actorName = TEXT("未命名演员");//演员名称
	FString description = TEXT("无描述。");//演员描述
	FString modelPath = TEXT("");//演员模型的路径
	FVector defaultPosition = FVector(0, 0, 0);//默认位置
	FVector defaultRotation = FVector(0, 0, 0);//默认角度

	TArray<FChat> chatList;//闲话列表
};
