// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SimpleUI.h"

#include "Events/EventBus.h"
#include "Events/UIEvents.h"
#include "Events/EventSubsystem.h"

void UDemoSimpleUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (UDemoEventBus* EventBus = UDemoEventSubsystem::GetGlobalEventBus(this); IsValid(EventBus))
	{
		EventBus->Dispatcher.AddUObject(this, &UDemoSimpleUI::OnAmmunitionChangedNative);
	}
}

void UDemoSimpleUI::OnAmmunitionChangedNative(UDemoEventBase* Event)
{
	const auto AmmunitionChanged = CastIfOnChannel<UDemoAmmunitionChangedEvent>(Event);
	if (!AmmunitionChanged) return;

	OnAmmunitionChanged(AmmunitionChanged->NewAmmunitionName);
}
