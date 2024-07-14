// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Event.h"
#include "UIEvents.generated.h"

UCLASS()
class UDemoAmmunitionChangedEvent : public UDemoEventBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText NewAmmunitionName{};
};
