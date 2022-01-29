// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Characteristics/GGJ_HealthComponent.h"


// Sets default values for this component's properties
UGGJ_HealthComponent::UGGJ_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

		DefaultHealth = 100.0f;
	CurrentHealth = DefaultHealth;
}

void UGGJ_HealthComponent::TakeDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType, class AController *InstigatedBy, AActor *DamagerCauser)
{
	if (Damage <= 0.0f)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, DefaultHealth);
	
}

// Called when the game starts
void UGGJ_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor *owner = GetOwner();

	if (owner)
	{
		owner->OnTakeAnyDamage.AddDynamic(this, &UGGJ_HealthComponent::TakeDamage);
	}	
}
