// Copyright Heliang Han 


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	this->WidgetController = InWidgetController;

	WidgetControllerSet();
}
