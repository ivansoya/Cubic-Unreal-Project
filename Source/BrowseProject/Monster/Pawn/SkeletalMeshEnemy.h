// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BrowseProject/Character/Interfaces/Stat.h"
#include "BrowseProject/Monster/Utility/EnemyData.h"
#include "SkeletalMeshEnemy.generated.h"

class ULootComponent;
class UEnemyStatComponent;
class UArrowComponent;
class UCapsuleComponent;

UCLASS()
class BROWSEPROJECT_API ASkeletalMeshEnemy : public APawn, public IStatInterface
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	ASkeletalMeshEnemy();


public:


private: 

	// ---------------------------------------------
	//	Ссылки на базы данных
	// ---------------------------------------------
	UPROPERTY(Category = "Monster Data Tables", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Enemy Data",
		RowType = "EnemyData", ToolTip = "Ref on a Row with monster stat data"))
	FDataTableRowHandle _EnemyData;

	// ---------------------------------------------
	//	Описание монстра
	// ---------------------------------------------
	UPROPERTY(Category = "Monster Info (Only Read)|00 - Description", VisibleAnywhere, meta = (DisplayName = "Name"))
	FString _Name;

	UPROPERTY(Category = "Monster Info (Only Read)|00 - Description", VisibleAnywhere, meta = (DisplayName = "Monster Class"))
	EMonsterClass _Class;

	// ---------------------------------------------
	//	Характеристики монстра
	// ---------------------------------------------
	UPROPERTY(Category = "Monster Info (Only Read)|01 - Monster Stats", VisibleAnywhere, meta = (DisplayName = "Current Health"))
	int32 _CurrentHealth;

	UPROPERTY(Category = "Monster Info (Only Read)|01 - Monster Stats", VisibleAnywhere, meta = (DisplayName = "Max Health"))
	int32 _MaxHealth;

	// Health regeneration per second
	UPROPERTY(Category = "Monster Info (Only Read)|01 - Monster Stats", VisibleAnywhere, meta = (DisplayName = "Health Regeneration"))
	int32 _RegenHealth;

	UPROPERTY(Category = "Monster Info (Only Read)|01 - Monster Stats", VisibleAnywhere, meta = (DisplayName = "Defense"))
	int32 _Defense;

	UPROPERTY(Category = "Monster Info (Only Read)|01 - Monster Stats", VisibleAnywhere, meta = (DisplayName = "Durability"))
	int32 _CurrentDurability;

	UPROPERTY(Category = "Monster Info (Only Read)|01 - Monster Stats", VisibleAnywhere, meta = (DisplayName = "Max Durability"))
	int32 _MaxDurability;

	// Восстановление стойкости в секунду
	UPROPERTY(Category = "Monster Info (Only Read)|01 - Monster Stats", VisibleAnywhere, meta = (DisplayName = "Durability Regeneration"))
	int32 _RegenDurability;

	// Время, через которое начинается регенерация стойкости, в с
	UPROPERTY(Category = "Monster Info (Only Read)|01 - Monster Stats", VisibleAnywhere, meta = (DisplayName = "Start Durability Regeneration"))
	int32 _StartRegenDurability;

	UPROPERTY(Category = "Monster Info (Only Read)|01 - Monster Stats", VisibleAnywhere, meta = (DisplayName = "Monster Stats"))
	TArray<FMonsterStatPair> _StatList = {
		FMonsterStatPair(EStatKey::STRENGTH, 0),
		FMonsterStatPair(EStatKey::DEXTERITY, 0),
		FMonsterStatPair(EStatKey::INTELLIGENCE, 0),
		FMonsterStatPair(EStatKey::ENDURANCE, 0),
	};

	UPROPERTY(Category = "Monster Info (Only Read)|01 - Monster Stats", VisibleAnywhere, meta = (DisplayName = "Monster Resistances"))
	TArray<FMonsterResistancePair> _ResistanceList;

	UPROPERTY(Category = "Monster Info (Only Read)|02 - Monster Damage", VisibleAnywhere, meta = (DisplayName = "Monster Damage", ShowOnlyInnerProperties))
	FMonsterDamage _MonsterDamage;

	UPROPERTY(Category = "Monster Info (Only Read)|03 - Monster Level", VisibleAnywhere, meta = (DisplayName = "Level", ShowOnlyInnerProperties))
	int32 _MonsterLevel;

	UPROPERTY(Category = "Monster Info (Only Read)|03 - Monster Level", VisibleAnywhere, meta = (DisplayName = "Exp Gained", ShowOnlyInnerProperties,
		ToolTip = "Exp gained buy player after killing this monster."))
	int32 _GainedExp;

private:
	// ---------------------------------------------
	//	Основные поля этого класса
	// ---------------------------------------------
	UPROPERTY(Category = "Components", VisibleAnywhere, meta = (DisplayName = "Stat Component"))
	TObjectPtr<UEnemyStatComponent> _StatComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "Skeletal Mesh Component"))
	TObjectPtr<USkeletalMeshComponent> _SkeletalMeshComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "Capsule Component"))
	TObjectPtr<UCapsuleComponent> _CapsuleComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "Loot"))
	TObjectPtr<ULootComponent> _LootComponent;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<UArrowComponent> _ArrowComponent;
#endif
	
public:

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	virtual void BeginCursorOver(UPrimitiveComponent* TouchedActor);

	UFUNCTION()
	virtual void EndCursorOver(UPrimitiveComponent* TouchedActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
