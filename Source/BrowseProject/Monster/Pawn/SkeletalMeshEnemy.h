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
	// --------------------------------------------
	//	Переопределение методов интерфейса IStat
	// --------------------------------------------


private:
	// ---------------------------------------------
	//	Основные поля этого класса
	// ---------------------------------------------
	UPROPERTY(Category = "Monster", VisibleAnywhere, meta = (DisplayName = "Stat Component"))
	TObjectPtr<UEnemyStatComponent> _StatComponent;

	UPROPERTY(Category = "Monster", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "Skeletal Mesh Component"))
	TObjectPtr<USkeletalMeshComponent> _SkeletalMeshComponent;

	UPROPERTY(Category = "Monster", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "Capsule Component"))
	TObjectPtr<UCapsuleComponent> _CapsuleComponent;

	UPROPERTY(Category = "Monster", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayName = "Loot"))
	TObjectPtr<ULootComponent> _LootComponent;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<UArrowComponent> _ArrowComponent;
#endif

	UPROPERTY(Category = "Monster Stats", VisibleAnywhere, meta = (DisplayName = "Health"))
	int32 _Health;

	UPROPERTY(Category = "Monster Stats", VisibleAnywhere, meta = (DisplayName = "Max Health"))
	int32 _MaxHealth;

	UPROPERTY(Category = "Monster Stats", VisibleAnywhere, meta = (DisplayName = "Durability"))
	int32 _Durability;

	UPROPERTY(Category = "Monster Stats", VisibleAnywhere, meta = (DisplayName = "Max Durability"))
	int32 _MaxDurability;

	UPROPERTY(Category = "Monster Data", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Enemy Data"))
	FDataTableRowHandle _EnemyData;
	
public:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
