// Copyright Heliang Han 


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfo);
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(Attributes);
	
	FAuraAttributeInfo Strength_AI = AttributeInfo->FindAttributeInfoForTag(
							FAuraGameplayTags::Get().Attributes_Primary_Strength);
	Strength_AI.AttributeValue = AS->GetStrength();

	OnAttributeInfo.Broadcast(Strength_AI);
}

void UAttributeMenuWidgetController::BindCallbackToDependencies()
{
	
}
