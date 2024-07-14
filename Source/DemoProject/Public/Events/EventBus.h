// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event.h"
#include "UObject/Object.h"
#include "EventBus.generated.h"

/**
 * This crude event system uses a plain Unreal delegate to send events. Delegates store callbacks in a simple array, so
 * when sending an event, for example FHeroDiedEvent, a whole array has to be traversed so that every observer has a
 * chance to receive the payload. This can be very slow if the whole game uses an event system like this.
 *
 * A better implementation could store callbacks in a multiset, like follows: \n
 * TMultiMap<TKey, ObserverEntry>, where TKey = TPair<EventClass, FName>
 *
 * This implementation makes sending events for the right observers take amortized O(1) time complexity instead of O(N)
 * for naive array traversal.
 */
UCLASS()
class DEMOPROJECT_API UDemoEventBus : public UObject
{
	GENERATED_BODY()

public:
	FDemoEvent Dispatcher;
};
