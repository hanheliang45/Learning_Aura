// Copyright Heliang Han 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectApplied_AssetsTags, const FGameplayTagContainer&)

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void SetAbilityActorInfo();

	FOnEffectApplied_AssetsTags OnEffectApplied_AssetsTags;
	
protected:

	void EffectApplied(UAbilitySystemComponent* ASC,
		const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
