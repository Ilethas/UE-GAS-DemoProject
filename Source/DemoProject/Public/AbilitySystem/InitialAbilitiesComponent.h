// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Templates/SubclassOf.h"
#include "InitialAbilitiesComponent.generated.h"


class UAbilitySystemComponent;
class UGameplayAbility;
class UGameplayEffect;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEMOPROJECT_API UDemoInitialAbilitiesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDemoInitialAbilitiesComponent();

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> InitialGameplayEffects;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> InitialAbilities;

	void ApplyEffects() const;
	void GrantAbilities() const;

	void GrantAbilitiesAndApplyEffectsOnce();
	bool bInitialized = false;

protected:
	UAbilitySystemComponent* GetAbilitySystemComponent() const;
};
