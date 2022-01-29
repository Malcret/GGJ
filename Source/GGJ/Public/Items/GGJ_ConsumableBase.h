// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact/GGJ_InteractableBase.h"
#include "GGJ_ConsumableBase.generated.h"

UENUM()
enum class CONSUMABLE_TYPE : uint8
{
	HealthRestoration UMETA(DisplayName = "HealthRestoration"),
	ManaRestoration UMETA(DisplayName = "ManaRestoration"),
	HealthRegeneration UMETA(DisplayName = "HealthRegeneration"),
	ManaRegeneration UMETA(DisplayName = "ManaRegeneration")
};

/**
 * 
 */
UCLASS()
class GGJ_API AGGJ_ConsumableBase : public AGGJ_InteractableBase
{
	GENERATED_BODY()

public:

	AGGJ_ConsumableBase();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	CONSUMABLE_TYPE ConsumableType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	float ConsumablePower;

public:

	virtual void OnInteract_Implementation(AActor *Caller);
	
};
