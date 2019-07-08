#include "PropertyBase.h"

void UPropertyBase::SetInfo(FString newPropertyName, float newPropertyValue)
{
	propertyName = newPropertyName;
	propertyValue = newPropertyValue;
}

float UPropertyBase::GetPropertyValue()
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
