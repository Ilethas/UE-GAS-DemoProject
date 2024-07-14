// Fill out your copyright notice in the Description page of Project Settings.


#include "Events/EventSubsystem.h"

#include "Events/EventBus.h"
#include "Kismet/GameplayStatics.h"

void UDemoEventSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	EventBus = NewObject<UDemoEventBus>(this);
}

UDemoEventBus* UDemoEventSubsystem::GetGlobalEventBus(const UObject* WorldContextObject)
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	return GameInstance ? GameInstance->GetSubsystem<UDemoEventSubsystem>()->EventBus : nullptr;
}
