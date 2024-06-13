// Fill out your copyright notice in the Description page of Project Settings.

#include "Affixes.h"
#include "BrowseProject/Character/Interfaces/Stat.h"

void UStatAffix::SetParams(TArray<FStatPair> StatList,
	TArray<FElementPair> ElementalDamageList,
	TArray<FElementPair> ElementalResistanceList,
	int32 TierNum, int32 Tier, FText Description)
{
	_StatList = StatList;
	_ElementalDamageList = ElementalDamageList;
	_ElementalResistanceList = ElementalResistanceList;
	_Description = Description;
	_NumberOfTiers = TierNum;
	_Tier = Tier;
}

void UStatAffix::Apply_Implementation(AActor* Actor)
{
	ChangeCharacterStatValues(Actor, true);
}

void UStatAffix::Cancel_Implementation(AActor* Actor)
{
	ChangeCharacterStatValues(Actor, false);
}

void UStatAffix::ChangeCharacterStatValues(AActor* Actor, bool IsPositive)
{
	auto t_StatComp = Cast<IStatInterface>(Actor);
	if (t_StatComp) {
		int32 k = 1;
		if (IsPositive == false) {
			k = -1;
		}
		for (auto t_Stat : _StatList) {
			IStatInterface::Execute_ChangeCharacterStatValue(Actor, t_Stat.Value * k, t_Stat.Key, EStatTypeRetuned::ADDED);
		}
		for (auto t_ElementalRes : _ElementalResistanceList) {
			IStatInterface::Execute_ChangeElementalValue(Actor, t_ElementalRes.Value * k, t_ElementalRes.DamageType, EStatElementalType::RESISTANCE);
		}
		for (auto t_ElementalDamage : _ElementalDamageList) {
			IStatInterface::Execute_ChangeElementalValue(Actor, t_ElementalDamage.Value * k, t_ElementalDamage.DamageType, EStatElementalType::DAMAGE_BONUS);
		}
	}
}

FText UStatAffix::GetText_Implementation()
{
	return FText();
}

template<typename T>
T* UItemDataFunctionLibrary::FindDataRowAfterCast(TObjectPtr<const UDataTable> DataTable, FName RowName) 
{
	if (DataTable == nullptr) {
		return nullptr;
	}
	if (DataTable->GetRowStruct() == T::StaticStruct()) {
		T* Data = DataTable->FindRow<T>(RowName, "");
		return Data;
	}
	return nullptr;
}

UObject* UItemDataFunctionLibrary::SpawnAffixFromTableRow(TObjectPtr<const UDataTable> DataTable, FName RowName, int32 Tier = 1)
{
	// ��������� ���� �� ������� ������
	if (DataTable == nullptr) {
		return nullptr;
	}
	// ��������� �������� �� ���������, ������� ������������� ������� �������������
	if (DataTable->GetRowStruct() == FStatAffixDataRow::StaticStruct()) {
		// ���� ������ � ������� �� ����������� �������� �������� ���� ������
		auto Data = DataTable->FindRow<FStatAffixDataRow>(RowName, "");
		if (Data == nullptr) {
			return nullptr;
		}
		// ������� ������� �� ����� ���� ������ �������������
		if (Data->TierNum < Tier || Tier < 1) {
			Tier = Data->TierNum;
		}
		// ��������� ��������� ���������� ��� �������� �� � ����������� ������� StatAffix
		TArray<FStatPair> StatParameters;
		TArray<FElementPair> ElementalDamage;
		TArray<FElementPair> ElementalResistances;
		// �������� �� ������� �������������, ������� ������������� ������
		for (auto Parameter : Data->Parameters) {
			int32 t_Value;
			// ���� �������� �������� ���������, ���������� ���
			if (Parameter.IsRandom == true) {
				t_Value = FMath::RandRange(Parameter.MinValue, Parameter.MaxValue);
			}
			// ����� ����� ������������� ��������
			else {
				t_Value = Parameter.ConstantValue;
			}
			// ��������� ������ �� ������ ������� ���������������
			// �� ����, ���� ����� ������� 8, � ������� ������� 1 (����� ������), �� �������� ������ �������� 7 ��������� ������ TierStep
			t_Value += Parameter.TierStep * (Data->TierNum - Tier);
			// ��������� � ���������� StatParameters
			StatParameters.Add(FStatPair(Parameter.Key, t_Value));
		}
		// ������� �� ������� ������� � �������������� �����
		for (auto ED : Data->ElementalDamages) {
			ElementalDamage.Add(UItemDataFunctionLibrary::GetElementalPair(ED, Data->TierNum, Tier));
		}
		// ������� �� ������� ������� � �������������� �������������
		for (auto ES : Data->ElementalResistances) {
			ElementalDamage.Add(UItemDataFunctionLibrary::GetElementalPair(ES, Data->TierNum, Tier));
		}
		UStatAffix* StatAffix = NewObject<UStatAffix>();
		StatAffix->SetParams(StatParameters, ElementalDamage, ElementalResistances, Data->TierNum, Tier, Data->Description);
		return StatAffix;
	}
	else return nullptr;
}

FElementPair UItemDataFunctionLibrary::GetElementalPair(const FElementParameter Parameter, int32 TierNum, int32 Tier)
{
	int32 t_Value;
	if (Parameter.IsRandom == true) {
		t_Value = FMath::RandRange(Parameter.MinValue, Parameter.MaxValue);
	}
	else {
		t_Value = Parameter.ConstantValue;
	}
	t_Value += Parameter.TierStep * (TierNum - Tier);
	return FElementPair(Parameter.Element, t_Value);
}
