// Copyright Heliang Han 


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::SetAbilityActorInfo()
{
	// this->OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
	this->OnGameplayEffectAppliedDelegateToSelf.AddLambda(
		[this](UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
												FActiveGameplayEffectHandle ActiveEffectHandle)
	{
			FGameplayTagContainer TagContainer;
			EffectSpec.GetAllAssetTags(TagContainer);
			OnEffectApplied_AssetsTags.Broadcast(TagContainer);
	});
}
// void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
//                                                 FActiveGameplayEffectHandle ActiveEffectHandle)
// {
// 	// GEngine->AddOnScreenDebugMessage(-1, 8, FColor::Blue, FString("Effect Applied"));
//
// 	FGameplayTagContainer TagContainer;
// 	EffectSpec.GetAllAssetTags(TagContainer);
//
// 	OnEffectApplied_AssetsTags.Broadcast(TagContainer);
// }
