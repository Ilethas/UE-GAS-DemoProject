// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Templates/SubclassOf.h"
#include "AmmunitionType.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
struct FGameplayEffectSpecHandle;
struct FDemoGameplayEffectSetterVisitor;

/**
 * Base abstract class for in-editor support of customizing GAS gameplay effects. Subclasses, such as
 * \a UDemoEffectMagnitudeSetter, can be created in DataAssets and later used to create \a GameplayEffectSpecs.
 * 
 * For example, you could have a \a GameplayEffect "GE_DealDamage" with amount of damage expected to be set
 * programatically and keep that amount inside an \a UDemoEffectMagnitudeSetter instance.
 *
 * Use \a FDemoGameplayEffectSetterVisitor to switch over actual object type.
 * 
 */
UCLASS(BlueprintType, Abstract, EditInlineNew, DefaultToInstanced)
class UDemoEffectSetter : public UObject
{
	GENERATED_BODY()

public:
	virtual void AcceptVisitor(FDemoGameplayEffectSetterVisitor& Visitor);
};

UCLASS()
class UDemoEffectMagnitudeSetter : public UDemoEffectSetter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FGameplayTag DataTag{};

	UPROPERTY(EditAnywhere)
	float Magnitude = 0.f;

	virtual void AcceptVisitor(FDemoGameplayEffectSetterVisitor& Visitor) override;
};

UCLASS()
class UDemoEffectLevelSetter : public UDemoEffectSetter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int Level = 1;

	virtual void AcceptVisitor(FDemoGameplayEffectSetterVisitor& Visitor) override;
};

UCLASS()
class UDemoEffectGameplayTagSetter : public UDemoEffectSetter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer DynamicTags{};

	virtual void AcceptVisitor(FDemoGameplayEffectSetterVisitor& Visitor) override;
};

/**
 * Use this interface to switch over actual \a UDemoEffectSetter object's type. Example usage could be like follows:
 
 * UDemoEffectSetter* Setter = GetMySetterFromSomewhere(); \n
 * Setter->AcceptVisitor(MyVisitor);	// MyVisitor inherits from \a FDemoGameplayEffectSetterVisitor
 */
struct FDemoGameplayEffectSetterVisitor
{
	virtual void Visit(UDemoEffectMagnitudeSetter* Setter) = 0;
	virtual void Visit(UDemoEffectLevelSetter* Setter) = 0;
	virtual void Visit(UDemoEffectGameplayTagSetter* Setter) = 0;

	virtual ~FDemoGameplayEffectSetterVisitor() = default;
};

USTRUCT(BlueprintType)
struct FDemoAmmunitionEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> Effect;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UDemoEffectSetter>> Setters;
};

/**
 * Allows creating assets with information about currently used ammunition, including:
 * - Ammunition Name.
 * - Array of gameplay effects to apply when projectiles of this ammunition type hit something. Each element has:
 *     - Gameplay Effect class that you want to use.
 *     - Array of setters that are used to create a \a FGameplayEffectSpec out of the Gameplay Effect class above.
 */
UCLASS(BlueprintType)
class DEMOPROJECT_API UDemoAmmunitionType : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Ammunition")
	FText Name;

	UPROPERTY(EditAnywhere, Category = "Ammunition")
	TArray<FDemoAmmunitionEffect> AppliedEffects;

	/** Creates an array of \a FGameplayEffectSpecs using \a GameplayEffects and \a Setters stored in \a AppliedEffects. */
	void MakeGameplayEffectSpecs(TArray<FGameplayEffectSpecHandle>& OutEffectSpecHandles,
	                             const UAbilitySystemComponent* AbilitySystemComponent,
	                             const UObject* NewSourceObject) const;
};
