// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Affixes.generated.h"

/**
 * Абстрактный класс всех аффиксов.
 * Содержит самые важные функции, которые необходимо переопределить в производных классах
 */
UCLASS(Abstract)
class BROWSEPROJECT_API UAffix : public UDataAsset
{
	GENERATED_BODY()

public:

	virtual void Apply();

	virtual void Cancel();

	virtual FText GetText();

private:

	UPROPERTY(EditAnywhere, Meta = (DisplayName = "Affix ID"))
	int _ID;

	UPROPERTY(EditAnywhere, Meta = (DisplayName = "Affix Description on Item"))
	FText _Description;

};

/**
 * Основной вид аффиксов в игре
 * Данный аффикс дает фиксированный бонус к характеристике персонажу
 * Класс содержит данные о типе характеристики, которая есть у персонажа и ее значение.
 */
UCLASS(Blueprintable)
class BROWSEPROJECT_API UBasicAffix : public UAffix
{
	GENERATED_BODY()

public:

	void Apply() override;

	void Cancel() override;

	FText GetText() override;

private:

	// Место для типа характеристики персонажа
	
	// Место для значения характеристики
};

/**
 * Аффикс, который дает персонажу пассивный эффект
 * Класс содержит данные об эффекте
 */
UCLASS(Blueprintable)
class BROWSEPROJECT_API UEquipAffix : public UAffix
{
	GENERATED_BODY()

public:

	void Apply() override;

	void Cancel() override;

	FText GetText() override;

private:

};

/**
 * Аффикс, который дает персонажу специальный эффект, который активируется при каком либо событии
 * Класс содержит данные об эффекте и привязанному событию
 */
UCLASS(Blueprintable)
class BROWSEPROJECT_API UTriggerAffix : public UAffix
{
	GENERATED_BODY()

public:

	void Apply() override;

	void Cancel() override;

	FText GetText() override;

private:

};
