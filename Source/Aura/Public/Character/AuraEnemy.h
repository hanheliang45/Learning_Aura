// Copyright Heliang Han 

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraBaseCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraBaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemy();

	// Enemy Interface start
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// Enemy Interface end

protected:
	virtual void BeginPlay() override;
};
