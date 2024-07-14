// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DamageCalculation.h"

#include "AbilitySystem/DemoAttributeSet.h"

UDemoDamageCalculation::UDemoDamageCalculation()
{
	// See https://github.com/tranek/GASDocumentation?tab=readme-ov-file#4511-modifier-magnitude-calculation
	// for more information on how to set up a GameplayModMagnitudeCalculation.

	NormalResistanceDef.AttributeToCapture = UDemoAttributeSet::GetNormalDamageResistanceAttribute();
	NormalResistanceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	NormalResistanceDef.bSnapshot = false;

	FireResistanceDef.AttributeToCapture = UDemoAttributeSet::GetFireDamageResistanceAttribute();
	FireResistanceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	FireResistanceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(NormalResistanceDef);
	RelevantAttributesToCapture.Add(FireResistanceDef);
}

float UDemoDamageCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags associated with the Spec (including dynamic tags)
	FGameplayTagContainer SpecTags;
	Spec.GetAllAssetTags(SpecTags);

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Damage = GetSetByCallerMagnitudeByTag(Spec, FGameplayTag::RequestGameplayTag("Gameplay.Magnitude.Damage"));
	if (SpecTags.HasTag(FGameplayTag::RequestGameplayTag("Gameplay.DamageType.Normal")))
	{
		float NormalResistance = 0.f;
		GetCapturedAttributeMagnitude(NormalResistanceDef, Spec, EvaluationParameters, NormalResistance);
		NormalResistance = FMath::Clamp(NormalResistance, 0.f, 1.f);
		Damage *= (1.f - NormalResistance);
	}
	else if (SpecTags.HasTag(FGameplayTag::RequestGameplayTag("Gameplay.DamageType.Fire")))
	{
		float FireResistance = 0.f;
		GetCapturedAttributeMagnitude(FireResistanceDef, Spec, EvaluationParameters, FireResistance);
		FireResistance = FMath::Clamp(FireResistance, 0.f, 1.f);
		Damage *= (1.f - FireResistance);
	}

	return Damage;
}
