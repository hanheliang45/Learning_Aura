// Copyright Heliang Han 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraBaseCharacter.generated.h"

UCLASS()
class AURA_API AAuraBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAuraBaseCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

};
