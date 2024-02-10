// Copyright Heliang Han 


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	UCharacterMovementComponent* characterMovementComponent = GetCharacterMovement();
	characterMovementComponent->bOrientRotationToMovement = true;
	characterMovementComponent->RotationRate = FRotator(0.f, 400.f, 0.f);
	characterMovementComponent->bConstrainToPlane = true;
	characterMovementComponent->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}
