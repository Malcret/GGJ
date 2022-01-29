// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GGJ_CharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "Interact/GGJ_InteractInterface.h"
#include "Characters/Characteristics/GGJ_HealthComponent.h"
#include "Characters/Characteristics/GGJ_ManaComponent.h"

// Sets default values
AGGJ_CharacterBase::AGGJ_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SpringArmComponent Initialization
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	// CameraComponent Initialization
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	// MeshComponent Initialization
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	// HealthComponent Initialization
	//HealthComponent = CreateDefaultSubobject<UGGJ_HealthComponent>(TEXT("HealthComponent"));
	//AddOwnedComponent(HealthComponent);

	// ManaComponent Initialization
	//ManaComponent = CreateDefaultSubobject<UGGJ_ManaComponent>(TEXT("ManaComponent"));
	//AddOwnedComponent(ManaComponent);

	// Camera
	BaseTurnRate = 45.0f;
	BaseLookUpAtRate = 45.0f;

	// Line tracing
	TraceDistance = 2000.0f;
	DebugTrace = false;

	// Push power
	DefaultPushForce = 1000.0f;
	CurrentPushForce = DefaultPushForce;
	DefaultPushCost = 10.0f;
	CurrentPushCost = DefaultPushCost;

	// Poll power
	DefaultPullForce = 500.0f;
	CurrentPullForce = DefaultPullForce;
	DefaultPullCost = 10.0f;
	CurrentPullCost = DefaultPullCost;
}

void AGGJ_CharacterBase::MoveForward(float value)
{
	if (Controller && value != 0.0f)
	{
		const FRotator yaw_rotation(0, Controller->GetControlRotation().Yaw, 0);
		const FVector direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, value);
	}
}

void AGGJ_CharacterBase::MoveRight(float value)
{
	if (Controller && value != 0.0f)
	{
		const FRotator yaw_rotation(0, Controller->GetControlRotation().Yaw, 0);
		const FVector direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, value);
	}
}

void AGGJ_CharacterBase::TurnAtRate(float value)
{
	AddControllerYawInput(value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGGJ_CharacterBase::LookUpAtRate(float value)
{
	AddControllerPitchInput(value * BaseLookUpAtRate * GetWorld()->GetDeltaSeconds());
}

void AGGJ_CharacterBase::InteractPressed()
{
	if (FocusActor)
	{
		IGGJ_InteractInterface *interface = Cast<IGGJ_InteractInterface>(FocusActor);
		if (interface)
		{
			interface->Execute_OnInteract(FocusActor, this);
		}
	}
}

void AGGJ_CharacterBase::TraceForward_Implementation()
{
	FVector location;
	FRotator rotation;
	FHitResult hit;

	GetController()->GetPlayerViewPoint(location, rotation);

	const FVector start = location;
	const FVector end = start + (rotation.Vector() * TraceDistance);

	const FCollisionQueryParams trace_params;
	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, trace_params))
	{
		if (DebugTrace)
		{
			DrawDebugLine(GetWorld(), start, hit.Location, FColor::Red, false, 2.0f);
			DrawDebugLine(GetWorld(), hit.Location, end, FColor::Green, false, 2.0f);
			DrawDebugSolidBox(GetWorld(), hit.Location, FVector(10.0f, 10.0f, 10.0f), FColor::Blue, false, 2.0f);
		}

		AActor *hited_actor = hit.GetActor();

		if (hited_actor && hited_actor != FocusActor)
		{
			if (FocusActor)
			{
				IGGJ_InteractInterface *interface = Cast<IGGJ_InteractInterface>(FocusActor);
				if (interface)
				{
					interface->Execute_EndFocus(FocusActor);
				}
			}
			IGGJ_InteractInterface *interface = Cast<IGGJ_InteractInterface>(hited_actor);
			if (interface)
			{
				interface->Execute_StartFocus(hited_actor);
			}
			FocusActor = hited_actor;
		}
	}
	else
	{
		if (DebugTrace)
		{
			DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 2.0f);
		}

		if (FocusActor)
		{
			IGGJ_InteractInterface *interface = Cast<IGGJ_InteractInterface>(FocusActor);
			if (interface)
			{
				interface->Execute_EndFocus(FocusActor);
			}
			FocusActor = nullptr;
		}
	}
}

void AGGJ_CharacterBase::FirePressed()
{
	PushPower();
}

void AGGJ_CharacterBase::SecondaryFirePressed()
{
	PullPower();
}

void AGGJ_CharacterBase::PushPower_Implementation()
{
	UseImpulse(1, CurrentPushForce);
	if(OnUsePower.IsBound())
	{
		OnUsePower.Broadcast(-CurrentPushCost);
	}
}

void AGGJ_CharacterBase::PullPower_Implementation()
{
	UseImpulse(-1, CurrentPullForce);
	if(OnUsePower.IsBound())
	{
		OnUsePower.Broadcast(-CurrentPullCost);
	}
}

void AGGJ_CharacterBase::OnOverlapBegin(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	IGGJ_InteractInterface *interface = Cast<IGGJ_InteractInterface>(OtherActor);
	if (interface)
	{
		interface->Execute_OnInteract(OtherActor, this);
	}
}

// Called when the game starts or when spawned
void AGGJ_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AGGJ_CharacterBase::OnOverlapBegin);
}

// Called every frame
void AGGJ_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TraceForward();
}

// Called to bind functionality to input
void AGGJ_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AGGJ_CharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGGJ_CharacterBase::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGGJ_CharacterBase::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGGJ_CharacterBase::LookUpAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AGGJ_CharacterBase::InteractPressed);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AGGJ_CharacterBase::FirePressed);
	PlayerInputComponent->BindAction("SecondaryFire", IE_Pressed, this, &AGGJ_CharacterBase::SecondaryFirePressed);
}

void AGGJ_CharacterBase::UseImpulse(const int8 Modificator, const float Force)
{
	FVector location;
	FRotator rotation;
	FHitResult hit;

	GetController()->GetPlayerViewPoint(location, rotation);

	const FVector start = location;
	const FVector end = start + (rotation.Vector() * TraceDistance);

	const FCollisionQueryParams trace_params;
	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, trace_params))
	{
		if (hit.GetActor()->IsRootComponentMovable())
		{
			UStaticMeshComponent *mesh_comp = Cast<UStaticMeshComponent>(hit.GetActor()->GetRootComponent());
			if (mesh_comp)
			{
				const FVector camera_forward = CameraComponent->GetForwardVector();
				mesh_comp->AddImpulse(Modificator * camera_forward * Force * mesh_comp->GetMass());
			}
		}
	}
}
