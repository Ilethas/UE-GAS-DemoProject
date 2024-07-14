// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASMacros.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "DemoAttributeSet.generated.h"

UCLASS()
class DEMOPROJECT_API UDemoAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "GAS | Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDemoAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "GAS | Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UDemoAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "GAS | Attributes | Resistances")
	FGameplayAttributeData NormalDamageResistance;
	ATTRIBUTE_ACCESSORS(UDemoAttributeSet, NormalDamageResistance)

	UPROPERTY(BlueprintReadOnly, Category = "GAS | Attributes | Resistances")
	FGameplayAttributeData FireDamageResistance;
	ATTRIBUTE_ACCESSORS(UDemoAttributeSet, FireDamageResistance)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:
	FString GetAvatarName() const;
};
