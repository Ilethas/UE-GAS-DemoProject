// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/InitialAbilitiesComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"

UDemoInitialAbilitiesComponent::UDemoInitialAbilitiesComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDemoInitialAbilitiesComponent::ApplyEffects() const
{
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (!AbilitySystemComponent) return;

	for (const TSubclassOf<UGameplayEffect>& InitialEffect : InitialGameplayEffects)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(GetOwner());

		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
			InitialEffect, 1.f, EffectContext);
		if (SpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void UDemoInitialAbilitiesComponent::GrantAbilities() const
{
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (!AbilitySystemComponent) return;

	for (const TSubclassOf<UGameplayAbility>& InitialAbility : InitialAbilities)
	{
		const FGameplayAbilitySpec GameplayAbilitySpec = FGameplayAbilitySpec(InitialAbility, 1);
		AbilitySystemComponent->GiveAbility(GameplayAbilitySpec);
	}
}

void UDemoInitialAbilitiesComponent::GrantAbilitiesAndApplyEffectsOnce()
{
	if (bInitialized)
		return;

	ApplyEffects();
	GrantAbilities();
	bInitialized = true;
}

UAbilitySystemComponent* UDemoInitialAbilitiesComponent::GetAbilitySystemComponent() const
{
	const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(GetOwner());
	if (!ensureMsgf(AbilitySystemInterface,
					TEXT("\"%s\": InitialAbilitiesComponent's owner actor should implement IAbilitySystemInterface"),
					*GetNameSafe(this)))
		return nullptr;

	UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();
	if (!ensureMsgf(AbilitySystemComponent,
					TEXT("\"%s\": Obtained AbilitySystemComponent shouldn't be nullptr"),
					*GetNameSafe(this)))
		return nullptr;

	return AbilitySystemComponent;
}
