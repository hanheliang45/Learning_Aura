// Copyright Heliang Han 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
public:
	void SetWidgetController(UObject* InWidgetController);
	
public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
};
