// Copyright Heliang Han 

#pragma once

#include "CoreMinimal.h"
#include "AuraBaseCharacter.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraBaseCharacter
{
	GENERATED_BODY()
public:
	AAuraCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Combat Interface **/
	virtual int32 GetPlayerLevel() override;
	/** Combat Interface End **/

protected:
	virtual void BeginPlay() override;

private:
	virtual void InitAbilityActorInfo() override;
};
