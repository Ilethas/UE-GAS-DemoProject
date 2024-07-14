// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthWidget.h"

#include "AbilitySystem/DemoAttributeSet.h"

void UDemoHealthWidget::OnHealthChangedNative(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data.NewValue);
}

void UDemoHealthWidget::OnMaxHealthChangedNative(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChanged(Data.NewValue);
}
