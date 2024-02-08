// Copyright Heliang Han 


#include "Character/AuraBaseCharacter.h"

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


