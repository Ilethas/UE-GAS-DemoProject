// Fill out your copyright notice in the Description page of Project Settings.


#include "Assets/AmmunitionType.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"

void UDemoEffectSetter::AcceptVisitor(FDemoGameplayEffectSetterVisitor& Visitor)
{
}

void UDemoEffectMagnitudeSetter::AcceptVisitor(FDemoGameplayEffectSetterVisitor& Visitor)
{
	Visitor.Visit(this);
}

void UDemoEffectLevelSetter::AcceptVisitor(FDemoGameplayEffectSetterVisitor& Visitor)
{
	Visitor.Visit(this);
}

void UDemoEffectGameplayTagSetter::AcceptVisitor(FDemoGameplayEffectSetterVisitor& Visitor)
{
	Visitor.Visit(this);
}

void UDemoAmmunitionType::MakeGameplayEffectSpecs(TArray<FGameplayEffectSpecHandle>& OutEffectSpecHandles,
                                                  const UAbilitySystemComponent* AbilitySystemComponent,
                                                  const UObject* NewSourceObject) const
{
	struct FVisitor : FDemoGameplayEffectSetterVisitor
	{
		const FGameplayEffectSpecHandle& Spec;

		explicit FVisitor(const FGameplayEffectSpecHandle& Spec) : Spec(Spec)
		{
		}

		virtual void Visit(UDemoEffectMagnitudeSetter* Setter) override
		{
			Spec.Data->SetSetByCallerMagnitude(Setter->DataTag, Setter->Magnitude);
		}

		virtual void Visit(UDemoEffectLevelSetter* Setter) override
		{
			Spec.Data->SetLevel(Setter->Level);
		}

		virtual void Visit(UDemoEffectGameplayTagSetter* Setter) override
		{
			Spec.Data->AppendDynamicAssetTags(Setter->DynamicTags);
		}
	};

	for (const auto& [Effect, Setters] : AppliedEffects)
	{
		if (!IsValid(Effect)) continue;

		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(NewSourceObject);

		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
			Effect, 1.f, EffectContext);
		if (SpecHandle.IsValid())
		{
			FVisitor EffectVisitor(SpecHandle);
			for (const TObjectPtr<UDemoEffectSetter>& Setter : Setters)
			{
				if (IsValid(Setter)) Setter->AcceptVisitor(EffectVisitor);
			}
			OutEffectSpecHandles.Add(SpecHandle);
		}
	}
}
