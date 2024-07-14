// Copyright Epic Games, Inc. All Rights Reserved.

#include "DemoProjectProjectile.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Assets/AmmunitionType.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ADemoProjectProjectile::ADemoProjectProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ADemoProjectProjectile::OnHit);
	// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ADemoProjectProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                   FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		IAbilitySystemInterface* SourceAbilitySystemInterface = Cast<IAbilitySystemInterface>(SourceObject);
		IAbilitySystemInterface* OtherAbilitySystemInterface = Cast<IAbilitySystemInterface>(OtherActor);
		if (OtherAbilitySystemInterface && SourceAbilitySystemInterface && GetValid(AmmunitionType))
		{
			UAbilitySystemComponent* SourceAbilitySystem = SourceAbilitySystemInterface->GetAbilitySystemComponent();
			UAbilitySystemComponent* OtherAbilitySystem = OtherAbilitySystemInterface->GetAbilitySystemComponent();

			if (IsValid(SourceAbilitySystem) && IsValid(OtherAbilitySystem))
			{
				TArray<FGameplayEffectSpecHandle> EffectSpecs;
				AmmunitionType->MakeGameplayEffectSpecs(EffectSpecs, SourceAbilitySystem, SourceObject);
				for (auto& Spec : EffectSpecs)
				{
					OtherAbilitySystem->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
				}
			}
			
			Destroy();
			return;
		}

		// Only add impulse and destroy projectile if we hit a physics
		if (OtherComp != nullptr && OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
			Destroy();
		}
	}
}
