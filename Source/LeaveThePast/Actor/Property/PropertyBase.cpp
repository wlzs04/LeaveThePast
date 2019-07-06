#include "PropertyBase.h"

void UPropertyBase::SetInfo(FString newPropertyName, FString newPropertyValue)
{
	propertyName = newPropertyName;
	propertyValue = newPropertyValue;
}

FString UPropertyBase::GetPropertyValue()
{
	return propertyValue;
}

FString UPropertyBase::GetPropertyName()
{
	return propertyName;
}

PropertyEnum UPropertyBase::GetPropertyType()
{
	return propertyEnum;
}
