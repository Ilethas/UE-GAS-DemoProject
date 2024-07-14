// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include <concepts>
#include "Event.generated.h"

UCLASS(Blueprintable)
class UDemoEventBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Event")
	FName Channel = NAME_None;
};

template <typename To, typename From>
	requires std::derived_from<To, UDemoEventBase> && std::derived_from<From, UDemoEventBase>
To* CastIfOnChannel(From* Event, const FName& Channel = NAME_None)
{
	if (!Event) return nullptr;
	return Event->Channel == Channel ? Cast<To>(Event) : nullptr;
}

DECLARE_MULTICAST_DELEGATE_OneParam(FDemoEvent, UDemoEventBase*);
