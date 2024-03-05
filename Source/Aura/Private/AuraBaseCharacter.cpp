// Copyright Heliang Han 


#include "Character/AuraBaseCharacter.h"

#include "AbilitySystemComponent.h"

AAuraBaseCharacter::AAuraBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	this->Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	this->Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	this->Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AAuraBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraBaseCharacter::InitAbilityActorInfo()
{
}

void AAuraBaseCharacter::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AAuraBaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GEClass, float level) const
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	check(ASC);
	check(DefaultPrimaryAttributes);

	FGameplayEffectContextHandle GEContextHandle = ASC->MakeEffectContext();
	GEContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle& SpecHandle = ASC->MakeOutgoingSpec(GEClass, level, GEContextHandle);
	ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC);
}

UAbilitySystemComponent* AAuraBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


