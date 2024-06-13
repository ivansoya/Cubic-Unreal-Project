// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BrowseProject/Monster/Utility/EnemyData.h"
#include "EnemyStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BROWSEPROJECT_API UEnemyStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyStatComponent();

	//UFUNCTION(BlueprintCallable, Category = "Dice Project|Monster Stat Component")
	void SetEnemyData(FEnemyData* Data);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
private:

	UPROPERTY(Category = "Stats", VisibleAnywhere, meta = (DisplayName = "Monster Stats"))
	TMap<EStatKey, int32> _Stats;

	UPROPERTY(Category = "Stats", VisibleAnywhere, meta = (DisplayName = "Monster Damage"))
	FMonsterDamage _Damage;

	UPROPERTY(Category = "Stats", VisibleAnywhere, meta = (DisplayName = "Monster Durability Regeneration"))
	int32 _RegenDurability;

	UPROPERTY(Category = "Stats", VisibleAnywhere, meta = (DisplayName = "Monster Start Durability Reneration Time"))
	int32 _StartRegenDurability;


};
