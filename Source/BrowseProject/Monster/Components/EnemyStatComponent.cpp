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

}
