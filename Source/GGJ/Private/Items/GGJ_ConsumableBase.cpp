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
