// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GGJ_PawnBase.h"


// Sets default values
AGGJ_PawnBase::AGGJ_PawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// MeshComponent Initialization
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGGJ_PawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void AGGJ_PawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

