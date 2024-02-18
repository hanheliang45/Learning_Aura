// Copyright Heliang Han 


#include "UI/WidgetController/OverlayWidgetController.h"

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
		.AddUObject(this, &UOverlayWidgetController::HealthChanged);
	this->AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetMaxHealthAttribute())
		.AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	this->AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetManaAttribute())
		.AddUObject(this, &UOverlayWidgetController::ManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
