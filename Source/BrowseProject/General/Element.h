// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Element.generated.h"

/**
 * ����� ��������� �������������� �����
 */
UCLASS()
class BROWSEPROJECT_API UElementalDamageType : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Meta = (DisplayName = "�������� ��������"))
	FString Name;

	UPROPERTY(BlueprintReadWrite, Meta = (DisplayName = "���� ������"))
	FColor TextColor;

	// ����� ��� �������, ������� ������������� ��� ��������� �����
};

/**
 * ��������� ��� ����������� ����� �������
 */
USTRUCT(BlueprintType)
struct FWeaponDamage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Elemental Damage Type"))
	UElementalDamageType* DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Minimal Additional Damage to Roll"))
	int MinDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Maximum Additional Damage to Roll"))
	int MaxDamage;
};

UCLASS()
class BROWSEPROJECT_API UElementalSystem : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Elemental Damage")
	static void SetEffectOnTarget();
};


