// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGJ_HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GGJ_API UGGJ_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGGJ_HealthComponent();

	UFUNCTION(BlueprintCallable)
	void Modification(const float Modificator);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float DefaultHealth;

	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth;

	UFUNCTION()
	void TakeDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType, class AController *InstigatedBy, AActor *DamagerCauser);

	// Called when the game starts
	virtual void BeginPlay() override;

public:
};
