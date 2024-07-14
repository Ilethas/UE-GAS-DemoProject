// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoPlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/DemoAttributeSet.h"
#include "AbilitySystem/InitialAbilitiesComponent.h"

ADemoPlayerState::ADemoPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UDemoAttributeSet>(TEXT("AttributeSet"));
	InitialAbilitiesComponent = CreateDefaultSubobject<UDemoInitialAbilitiesComponent>(
		TEXT("InitialAbilitiesComponent"));
}

UAbilitySystemComponent* ADemoPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UDemoAttributeSet* ADemoPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

void ADemoPlayerState::InitAbilitySystemComponent() const
{
	InitialAbilitiesComponent->GrantAbilitiesAndApplyEffectsOnce();
}
