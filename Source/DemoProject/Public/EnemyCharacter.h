// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UDemoInitialAbilitiesComponent;
class UWidgetComponent;
class UDemoAttributeSet;

UCLASS()
class DEMOPROJECT_API ADemoEnemyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADemoEnemyCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> HealthWidgetComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UDemoAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UDemoInitialAbilitiesComponent> InitialAbilitiesComponent;
	
	virtual UDemoAttributeSet* GetAttributeSet() const;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
