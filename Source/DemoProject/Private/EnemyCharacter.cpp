// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/DemoAttributeSet.h"
#include "AbilitySystem/InitialAbilitiesComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/HealthWidget.h"


// Sets default values
ADemoEnemyCharacter::ADemoEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidgetComponent"));
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UDemoAttributeSet>(TEXT("AttributeSet"));
	InitialAbilitiesComponent = CreateDefaultSubobject<UDemoInitialAbilitiesComponent>(
		TEXT("InitialAbilitiesComponent"));
}

// Called every frame
void ADemoEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADemoEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* ADemoEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UDemoAttributeSet* ADemoEnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

// Called when the game starts or when spawned
void ADemoEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	if (UDemoHealthWidget* HealthWidget = Cast<UDemoHealthWidget>(HealthWidgetComponent->GetWidget());
		IsValid(HealthWidget))
	{
		FOnGameplayAttributeValueChange& HealthChanged = AbilitySystemComponent->
			GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute());
		HealthChanged.AddUObject(HealthWidget, &UDemoHealthWidget::OnHealthChangedNative);

		FOnGameplayAttributeValueChange& MaxHealthChanged = AbilitySystemComponent->
			GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute());
		MaxHealthChanged.AddUObject(HealthWidget, &UDemoHealthWidget::OnMaxHealthChangedNative);
	}
	InitialAbilitiesComponent->GrantAbilitiesAndApplyEffectsOnce();
}
