// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SimpleUI.generated.h"

class UDemoEventBase;
class UTextBlock;

UCLASS()
class DEMOPROJECT_API UDemoSimpleUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnAmmunitionChanged(const FText& NewAmmunitionName);

private:
	void OnAmmunitionChangedNative(UDemoEventBase* Event);
};
