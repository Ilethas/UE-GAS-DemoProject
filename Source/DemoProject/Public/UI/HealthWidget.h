// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

struct FOnAttributeChangeData;

UCLASS()
class DEMOPROJECT_API UDemoHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(const float NewHealthValue);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnMaxHealthChanged(const float NewMaxHealthValue);
	
	void OnHealthChangedNative(const FOnAttributeChangeData& Data);
	void OnMaxHealthChangedNative(const FOnAttributeChangeData& Data);
};
