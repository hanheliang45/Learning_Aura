// Copyright Heliang Han 


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	this->Mesh = this->CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(this->Mesh);
	
	this->Sphere = this->CreateDefaultSubobject<USphereComponent>("Sphere");
	this->Sphere->SetupAttachment(this->GetRootComponent());
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UAttributeSet* AttributeSet = ASCInterface
			->GetAbilitySystemComponent()
			->GetAttributeSet(UAuraAttributeSet::StaticClass());
		UAuraAttributeSet* AuraAttributeSet = const_cast<UAuraAttributeSet*>(
															Cast<UAuraAttributeSet>(AttributeSet));
		AuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
		AuraAttributeSet->SetMana(AuraAttributeSet->GetMana() - 5.f);
		Destroy();
	}
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	this->Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	this->Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}

