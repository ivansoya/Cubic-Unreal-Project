// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStatComponent.h"

UEnemyStatComponent::UEnemyStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UEnemyStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UEnemyStatComponent::SetEnemyData(FEnemyData* Data)
{
	// копирование структуры урона
	_Damage = Data->Damage;
	// ƒобавление характеристик в список
	for (auto& t_StatPair : Data->StatList) {
		_Stats.Add(TPair<EStatKey, int32>(t_StatPair.Stat, t_StatPair.Value));
	}
	// «начение прочих характеристик
	_RegenDurability = Data->RegenDurability;
	_StartRegenDurability = Data->StartRegenDurability;

}
