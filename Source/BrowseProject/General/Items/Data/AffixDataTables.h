// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrowseProject/General/Stats/StatEnums.h"
#include "BrowseProject/General/Element/ElementalDamageType.h"
#include "AffixDataTables.generated.h"


USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FBaseParameter
{
	GENERATED_BODY()

	// ��������, �� ������� ����� ������������� �������� ������� ��� ��������� ������ ���������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Tier Step Value", DisplayPriority = "2"))
	int32 TierStep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Is Random", DisplayPriority = "3"))
	bool IsRandom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Constant Value of Parameter", EditCondition = "IsRandom == false", DisplayPriority = "4"))
	int32 ConstantValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Min Value of Parameter", EditCondition = "IsRandom == true", DisplayPriority = "5"))
	int32 MinValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Max Value of Parameter", EditCondition = "IsRandom == true", DisplayPriority = "6"))
	int32 MaxValue;

};

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FStatParameter : public FBaseParameter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Key of Parameter", DisplayPriority = "1"))
	EStatKey Key;
};

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FElementParameter : public FBaseParameter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Type of Element", EditCondition = "IsAllElements == false", DisplayPriority = "1"))
	UElementalDamageType* Element;
};


/// <summary>
/// ��������� ��� �������, ���������������� �������� �������������� ���������
/// ������ ����� ����� ������ ���������� �������, ������� ������������ ����������
/// </summary>
USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FStatAffixDataRow : public FTableRowBase
{
	GENERATED_BODY()

	// ������������� �������� ������� �������
	// ��������� �� ������ ������� ���������� ����������� ��� %[������ ������� Parameters]
	// ��������� �� ������ �������������� ����� ����������� ��� #[������ ������� ElementalDamages]
	// ��������� �� ������ �������������� ������������� ����������� ��� &[������ ������� ElementalResistances]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Description"));
	FText Description;

	// ���������� ������� � �������
	// ��� ���� ������� - ��� ���� ��������, ����� ������� 1 ��� - ������ �������� ����� ������ � ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Number of Tiers"));
	int32 TierNum;

	// ������ ������� ����������, ������� ������������� �������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "List of Parameters"))
	TArray<FStatParameter> Parameters;

	// ������ ������� � �������������� �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "List of Elemental Damage Types Bonuses"))
	TArray<FElementParameter> ElementalDamages;

	// ������ ������������� �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "List of Elemental Resistances Values"))
	TArray<FElementParameter> ElementalResistances;

};