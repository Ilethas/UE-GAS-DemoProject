// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DemoAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Logs.h"

void UDemoAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.f);
	}
	else if (Attribute == GetNormalDamageResistanceAttribute() || Attribute == GetFireDamageResistanceAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, 1.f);
	}
}

void UDemoAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	UE_LOG(DemoGameplay, Log, TEXT("Effect \"%s\" applied to: %s"), *Data.EffectSpec.ToSimpleString(),
	       *GetAvatarName());

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		UE_LOG(DemoGameplay, Log, TEXT("%s: changed Health to %f"), *GetAvatarName(), GetHealth());
	}
	else if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		SetMaxHealth(FMath::Max(GetMaxHealth(), 1.f));
		UE_LOG(DemoGameplay, Log, TEXT("%s: changed MaxHealth to %f"), *GetAvatarName(), GetMaxHealth());
	}
	else if (Data.EvaluatedData.Attribute == GetNormalDamageResistanceAttribute())
	{
		SetNormalDamageResistance(FMath::Clamp(GetNormalDamageResistance(), 0.f, 1.f));
		UE_LOG(DemoGameplay, Log, TEXT("%s: changed NormalDamageResistance to %f"), *GetAvatarName(), GetNormalDamageResistance());
	}
	else if (Data.EvaluatedData.Attribute == GetFireDamageResistanceAttribute())
	{
		SetFireDamageResistance(FMath::Clamp(GetFireDamageResistance(), 0.f, 1.f));
		UE_LOG(DemoGameplay, Log, TEXT("%s: changed FireDamageResistance to %f"), *GetAvatarName(), GetFireDamageResistance());
	}
}

FString UDemoAttributeSet::GetAvatarName() const
{
	if (const TWeakObjectPtr<AActor> WeakAvatarActor = GetActorInfo()->AvatarActor; WeakAvatarActor.IsValid())
	{
		return GetNameSafe(WeakAvatarActor.Get());
	}
	return "<AvatarActor missing>";
}
