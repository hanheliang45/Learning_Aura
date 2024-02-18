// Copyright Heliang Han 


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	this->bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	this->CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(auraContext);
	
	UEnhancedInputLocalPlayerSubsystem* subSysTem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(subSysTem)
	{
		subSysTem->AddMappingContext(auraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetHideCursorDuringCapture(false);
	this->SetInputMode(inputModeData);


}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(Super::InputComponent);

	enhancedInputComponent->BindAction(moveAction, 
		ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& inputActionValue)
{
	const FVector2D inputAxisVector = inputActionValue.Get<FVector2D>();

	const FRotator rotation = GetControlRotation();
	const FRotator yawRotation(0.f, rotation.Yaw, 0.f);

	const FVector forwardDierction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* controlledPawn = GetPawn<APawn>())
	{
		controlledPawn->AddMovementInput(forwardDierction, inputAxisVector.Y);
		controlledPawn->AddMovementInput(rightDirection, inputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult cursorHit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, cursorHit);
	if (!cursorHit.bBlockingHit) return;

	IEnemyInterface* hoveringEnemy = Cast<IEnemyInterface>(cursorHit.GetActor());

	if (lastHoveringEnemy == nullptr)
	{
		if (hoveringEnemy == nullptr)
		{
		
		}
		else
		{
			hoveringEnemy->HighlightActor();
		}
	}
	else
	{
		if (hoveringEnemy == nullptr)
		{
			lastHoveringEnemy->UnHighlightActor();
		}
		else if (lastHoveringEnemy != hoveringEnemy)
		{
			lastHoveringEnemy->UnHighlightActor();
			hoveringEnemy->HighlightActor();
		}
	}

	lastHoveringEnemy = hoveringEnemy;
}
