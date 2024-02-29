// Copyright Heliang Han 


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const TObjectPtr<UAuraAttributeSet> AuraAttributes = CastChecked<UAuraAttributeSet>(this->Attributes);
	OnHealthChanged.Broadcast(AuraAttributes->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributes->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributes->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributes->GetMaxMana());
}

void UOverlayWidgetController::BindCallbackToDependencies()
{
	const TObjectPtr<UAuraAttributeSet> AuraAttributes = CastChecked<UAuraAttributeSet>(this->Attributes);

	this->AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		});
	this->AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetMaxHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});
	this->AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetManaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		});
	this->AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetMaxManaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		});
	
	Cast<UAuraAbilitySystemComponent>(this->AbilitySystemComponent)->OnEffectApplied_AssetsTags.AddLambda(
		[this](const FGameplayTagContainer& TagContainer)
		{
			for (const FGameplayTag& Tag : TagContainer)
			{
				// const FString Msg = FString::Printf(TEXT("GE tag: %s"), *Tag.ToString());
				// GEngine->AddOnScreenDebugMessage(-1, 8, FColor::Blue, Msg);

				FUIWidgetRow* UIWidgetRow = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);

				if (UIWidgetRow->Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message"))))
				{
					OnEffectApplied_Message.Broadcast(*UIWidgetRow);
				}
			}
		}
	);
}

