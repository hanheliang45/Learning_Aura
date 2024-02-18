// Copyright Heliang Han 


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

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

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	
	this->AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	this->AttributeSet = AuraPlayerState->GetAttributeSet();
	
	this->AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);

	if (AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* HUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			HUD->InitOverlay(
				PlayerController,
				AuraPlayerState,
				this->AbilitySystemComponent,
				this->AttributeSet);
			
		}
	}
}
