// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/GGJ_InteractableBase.h"


// Sets default values
AGGJ_InteractableBase::AGGJ_InteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGGJ_InteractableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGGJ_InteractableBase::OnInteract_Implementation(AActor *Caller)
{
	Destroy();
}

void AGGJ_InteractableBase::StartFocus_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Start Focus"));
}

void AGGJ_InteractableBase::EndFocus_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("End Focus"));
}
