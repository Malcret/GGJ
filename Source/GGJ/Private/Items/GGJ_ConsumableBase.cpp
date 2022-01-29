// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/GGJ_ConsumableBase.h"
#include "Characters/GGJ_CharacterBase.h"
#include "Characters/Characteristics/GGJ_HealthComponent.h"
#include "Characters/Characteristics/GGJ_ManaComponent.h"

AGGJ_ConsumableBase::AGGJ_ConsumableBase()
{
    ConsumableType = CONSUMABLE_TYPE::HealthRestoration;
    ConsumablePower = 20.0f;
}

void AGGJ_ConsumableBase::OnInteract_Implementation(AActor *Caller)
{

    AGGJ_CharacterBase *actor = Cast<AGGJ_CharacterBase>(Caller);

    if (actor)
    {
        switch (ConsumableType)
        {
            case CONSUMABLE_TYPE::HealthRestoration:
                actor->HealthComponent->Modification(ConsumablePower);
                break;
            case CONSUMABLE_TYPE::ManaRestoration:
                actor->ManaComponent->Modification(ConsumablePower);        
            default:
                break;
        }
    }

    Destroy();
}
