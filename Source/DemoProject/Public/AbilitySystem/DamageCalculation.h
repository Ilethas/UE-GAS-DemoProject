// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "DamageCalculation.generated.h"

UCLASS()
class DEMOPROJECT_API UDemoDamageCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UDemoDamageCalculation();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	UPROPERTY()
	FGameplayEffectAttributeCaptureDefinition NormalResistanceDef;
	
	UPROPERTY()
	FGameplayEffectAttributeCaptureDefinition FireResistanceDef;
};
