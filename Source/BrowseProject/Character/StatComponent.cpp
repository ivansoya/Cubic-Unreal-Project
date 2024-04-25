// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"
#include "BrowseProject/General/Element.h"

UStatComponent::UStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UStatComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UStatComponent::OnComponentCreated()
{
	Super::OnComponentCreated();

	// Устанавливает дефолтные значения для персонажа
	if (_DefaultStats) {
		// Дефолтные значения для обычных характеристик
		for (auto pair_r : _DefaultStats->StatList) {
			_Stats.Add(pair_r.Key, FStatValues(pair_r.Value, 0));
		}

		// Дефолтные значения сопротивлений
		for (auto pair_res : _DefaultStats->Resistances) {
			_Resistances.Add(pair_res.Key, pair_res.Value);
		}

		// Дефолтные значения повышения элементального урона
		for (auto pair_elem : _DefaultStats->ExtraElementalDamage) {
			_ExtraElementalDamage.Add(pair_elem.Key, pair_elem.Value);
		}
	}
}

void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatComponent::AddStatValue(EStatKey Stat, int32 Value, EStatTypeRetuned AddTo)
{
	auto stat_t = _Stats.Find(Stat);
	if (stat_t) {
		// Проверяем, какое именно значение нужно изменить
		// Добавочное или базовое
		switch (AddTo) {
		case EStatTypeRetuned::ADDED:
			(*stat_t).AddedValue += Value;
			break;
		case EStatTypeRetuned::BASE:
			(*stat_t).Base += Value;
			break;
		case EStatTypeRetuned::GENERAL:
		default:
			break;
		}
	}
	// Если не нашли такой характеристики в списке
	else {
		_Stats.Add(Stat, FStatValues(Value, 0));
	}
	return;
}

int32 UStatComponent::GetStatValue(EStatKey Stat, EStatTypeRetuned StatType) const
{
	auto stat_t = _Stats.Find(Stat);
	if (stat_t) {
		switch (StatType)
		{
		case EStatTypeRetuned::GENERAL:
			return (*stat_t).AddedValue + (*stat_t).Base;
			break;
		case EStatTypeRetuned::BASE:
			return (*stat_t).Base;
			break;
		case EStatTypeRetuned::ADDED:
			return (*stat_t).AddedValue;
			break;
		default:
			return 0;
			break;
		}
	}
	else {
		return 0;
	}
}

void UStatComponent::AddElementalResistanceValue(UElementalDamageType* Elemental, int32 Value)
{
	auto res_t = _Resistances.Find(Elemental);
	if (res_t) {
		(*res_t).Current += Value;
		return;
	}
	return;
}

void UStatComponent::AddMaximumElementalResistanceValue(UElementalDamageType* Elemental, int32 Value)
{
	auto res_t = _Resistances.Find(Elemental);
	if (res_t) {
		(*res_t).MaxValue += Value;
		return;
	}
	return;
}

int32 UStatComponent::GetElementalResistanceValue(UElementalDamageType* Elemental) const
{
	auto res_t = _Resistances.Find(Elemental);
	if (res_t) {
		if ((*res_t).MaxValue < (*res_t).Current) {
			return (*res_t).MaxValue;
		}
		return (*res_t).Current;
	}
	return 0;
}

void UStatComponent::AddExtraElementalDamage(UElementalDamageType* Elemental, int32 Value)
{
	auto elemd_t = _ExtraElementalDamage.Find(Elemental);
	if (elemd_t) {
		(*elemd_t) += Value;
		return;
	}
	else {
		_ExtraElementalDamage.Add(Elemental, Value);
		return;
	}
}

int32 UStatComponent::GetElementalExtraDamage(UElementalDamageType* Elemental) const
{
	auto elemd_t = _ExtraElementalDamage.Find(Elemental);
	if (elemd_t) {
		return (*elemd_t);
	}
	else {
		return 0;
	}
}

TMap<EStatKey, FStatValues> UStatComponent::GetCharacterStats() const
{
	return _Stats;
}

TMap<UElementalDamageType*, FResistanceValue> UStatComponent::GetElementalResistance() const
{
	return _Resistances;
}

TMap<UElementalDamageType*, int32> UStatComponent::GetExtraElementalDamage() const
{
	return _ExtraElementalDamage;
}