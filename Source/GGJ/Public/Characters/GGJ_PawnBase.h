// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GGJ_PawnBase.generated.h"

UCLASS()
class GGJ_API AGGJ_PawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGGJ_PawnBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	class UStaticMeshComponent *MeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
