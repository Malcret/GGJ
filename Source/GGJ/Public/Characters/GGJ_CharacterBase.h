// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GGJ_CharacterBase.generated.h"

UCLASS()
class GGJ_API AGGJ_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGGJ_CharacterBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent *SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent *CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	class UStaticMeshComponent *MeshComponent;

protected:

	// Camera movements rates
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpAtRate;

	// Line tracing
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float TraceDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool DebugTrace;

	UPROPERTY(EditAnywhere, Category = "Impulsion")
	float ImpulseForce;

	// Character movements
	void MoveForward(float value);
	void MoveRight(float value);

	// Camera movements
	void TurnAtRate(float value);
	void LookUpAtRate(float value);

	// Interact
	void InteractPressed();

	// Trace a line from the camera to the camera pointing location
	UFUNCTION(BlueprintNativeEvent)
	void TraceForward();
	void TraceForward_Implementation();

	void FirePressed();

	UFUNCTION(BlueprintNativeEvent)
	void FireForward();
	void FireForward_Implementation();

	// Called on overlapping
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	AActor *FocusActor;
};
