#include "SetTimeAction.h"
#include "../Manager/HelpManager.h"
#include "../Manager/MainGameManager.h"

USetTimeAction::USetTimeAction() :UActionBase()
{
	actionName = TEXT("SetTime");
}

void USetTimeAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("time"))
		{
			FTimespan timespan = UHelpManager::ConvertFStringToFTimespan(attributeValue);
			timeData.SetTime(timespan.GetHours(), timespan.GetMinutes(), timespan.GetSeconds());
		}
	}
}

void USetTimeAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetTimeAction::ExecuteReal()
{
	isCompleted = false;
	UMainGameManager::GetInstance()->GetUserData()->SetGameTime(timeData.GetHours(), timeData.GetMinutes(), timeData.GetSeconds());
	return FString();
}