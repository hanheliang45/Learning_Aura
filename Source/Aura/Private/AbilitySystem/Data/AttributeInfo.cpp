// Copyright Heliang Han 


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound)
{
	for(const FAuraAttributeInfo& info : AttributeInfos)
	{
		if (info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("cant' find info for AttributeTag [%s] on AttributeInfos [%s]."),
			*AttributeTag.ToString(), *GetNameSafe(this)
		);
	}

	return FAuraAttributeInfo();
}
