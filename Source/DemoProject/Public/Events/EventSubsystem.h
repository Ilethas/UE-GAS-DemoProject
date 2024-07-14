// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EventSubsystem.generated.h"

class UDemoEventBus;

UCLASS()
class DEMOPROJECT_API UDemoEventSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Event Subsystem")
	TObjectPtr<UDemoEventBus> EventBus;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(
		BlueprintPure,
		Meta = (WorldContext = "WorldContextObject", CompactNodeTitle = "Global Event Bus"),
		Category = "Event Subsystem")
	static UDemoEventBus* GetGlobalEventBus(const UObject* WorldContextObject);
};
