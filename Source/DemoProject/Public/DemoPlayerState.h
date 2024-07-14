// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "DemoPlayerState.generated.h"

class UDemoAttributeSet;
class UDemoInitialAbilitiesComponent;

UCLASS()
class DEMOPROJECT_API ADemoPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UDemoAttributeSet> AttributeSet;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UDemoInitialAbilitiesComponent> InitialAbilitiesComponent;

public:
	ADemoPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UDemoAttributeSet* GetAttributeSet() const;
	void InitAbilitySystemComponent() const;
};
