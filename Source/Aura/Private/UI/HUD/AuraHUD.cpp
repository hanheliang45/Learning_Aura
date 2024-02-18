// Copyright Heliang Han 


#include "UI/HUD/AuraHUD.h"

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class is null."));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class is null."));

	const FWidgetControllerParams WCParams(PC, PS, ASC, AS);
	GetOverlayWidgetController(WCParams);
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	OverlayWidget->SetWidgetController(this->OverlayWidgetController);

	this->OverlayWidgetController->BroadcastInitialValues();
	this->OverlayWidgetController->BindCallbackToDependencies();
	Widget->AddToViewport();
}

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (this->OverlayWidgetController == nullptr)
	{
		this->OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		this->OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}

	return this->OverlayWidgetController;
}

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
}
