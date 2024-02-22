// Copyright Heliang Han 


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootComponent"));
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* EffectTarget, TSubclassOf<UGameplayEffect> GameEffectClass)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectTarget);
	if (ASC == nullptr) return;

	check(GameEffectClass);
	
	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GameEffectClass, 1.f, ContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle =ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
	if (SpecHandle.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite
		&& this->InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectDictionary.Add(ActiveEffectHandle, ASC);
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (this->InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, this->InfiniteGameplayEffectClass);
	}
	if (this->DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, this->DurationGameplayEffectClass);
	}
	if (this->InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, this->InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (this->InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, this->InstantGameplayEffectClass);
	}
	if (this->DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, this->DurationGameplayEffectClass);
	}
	if (this->InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, this->InfiniteGameplayEffectClass);
	}
	if (this->InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (IsValid(ASC))
		{
			TArray<FActiveGameplayEffectHandle> EffectHandlesToRemove;
			for (auto Entry : ActiveEffectDictionary)
			{
				if (Entry.Value == ASC)
				{
					ASC->RemoveActiveGameplayEffect(Entry.Key, 1);
					EffectHandlesToRemove.Add(Entry.Key);
				}
			}
			for (auto Handle : EffectHandlesToRemove)
			{
				ActiveEffectDictionary.FindAndRemoveChecked(Handle);
			}
		}
	}
}

