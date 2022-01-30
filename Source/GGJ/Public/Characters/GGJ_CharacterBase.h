// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GGJ_CharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUsePowerSignature, const float, ManaCost);

UENUM()
enum class CHARACTER_STATE : uint8
{
	Good UMETA(DisplayName = "Good"),
	Neutral UMETA(DisplayName = "Neutral"),
	Evil UMETA(DisplayName = "Evil")
};

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

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//class UGGJ_HealthComponent *HealthComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//class UGGJ_ManaComponent *ManaComponent;

	UPROPERTY(BlueprintAssignable)
	FOnUsePowerSignature OnUsePower;

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

	// Push power
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float DefaultPushForce;
	UPROPERTY(BlueprintReadOnly)
	float CurrentPushForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float DefaultPushCost;
	UPROPERTY(BlueprintReadOnly)
	float CurrentPushCost;

	// Pull power
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float DefaultPullForce;
	UPROPERTY(BlueprintReadOnly)
	float CurrentPullForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float DefaultPullCost;
	UPROPERTY(BlueprintReadOnly)
	float CurrentPullCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	CHARACTER_STATE CharacterState;

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
	void SecondaryFirePressed();

	UFUNCTION(BlueprintNativeEvent)
	void PushPower();
	void PushPower_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void PullPower();
	void PullPower_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void ChangeState(CHARACTER_STATE state);
	void ChangeState_Implementation(CHARACTER_STATE state);

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

	void UseImpulse(const int8 Modificator, const float Force);
};
