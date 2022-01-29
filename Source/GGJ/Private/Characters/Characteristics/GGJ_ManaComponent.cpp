// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Characteristics/GGJ_ManaComponent.h"
#include "Characters/GGJ_CharacterBase.h"


// Sets default values for this component's properties
UGGJ_ManaComponent::UGGJ_ManaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	DefaultMana = 100.0f;
	DefaultManaRegenRate = 1.0f;

	CurrentMana = DefaultMana;
	CurrentManaRegenRate = DefaultManaRegenRate;
}

void UGGJ_ManaComponent::Modification(const float Modificator)
{
	if (Modificator != 0.0f)
	{
		CurrentMana = FMath::Clamp(CurrentMana + Modificator, 0.0f, DefaultMana);
	}
}


// Called when the game starts
void UGGJ_ManaComponent::BeginPlay()
{
	Super::BeginPlay();

	AGGJ_CharacterBase *owner = Cast<AGGJ_CharacterBase>(GetOwner());
	
	if (owner)
	{
		owner->OnUsePower.AddDynamic(this, &UGGJ_ManaComponent::Modification);
	}
}
