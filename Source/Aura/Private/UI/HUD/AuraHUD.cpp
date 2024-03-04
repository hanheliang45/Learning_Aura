// Copyright Heliang Han 


#include "UI/HUD/AuraHUD.h"

#include "UI/WidgetController/AttributeMenuWidgetController.h"

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
	
	Widget->AddToViewport();
}

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (this->OverlayWidgetController == nullptr)
	{
		this->OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		this->OverlayWidgetController->SetWidgetControllerParams(WCParams);
		this->OverlayWidgetController->BindCallbackToDependencies();
	}

	return this->OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (this->AttributeMenuWidgetController == nullptr)
	{
		this->AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		this->AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		this->AttributeMenuWidgetController->BindCallbackToDependencies();
	}
	return this->AttributeMenuWidgetController;
}

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
}
