// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AffixesData.h"
#include "Affixes.generated.h"

/**
 * Абстрактный класс всех аффиксов.
 * Содержит самые важные функции, которые необходимо переопределить в производных классах
 */
class BROWSEPROJECT_API UAffix
{

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Affix Description on Item"))
	FText Description;

public: 

	/// <summary>
	/// Функция для применения аффикса на персонажа
	/// </summary>
	/// <returns></returns>
	virtual void Apply() = 0;

	/// <summary>
	/// Функция для отмены аффикса на персонаже
	/// </summary>
	/// <returns></returns>
	virtual void Cancel() = 0;

	/// <summary>
	/// Функция возвращает текст описания аффикса
	/// </summary>
	/// <returns>Текст описания</returns>
	virtual FText GetText() = 0;

private:

	UPROPERTY(VisibleAnywhere, Meta = (DisplayName = "Affix ID"))
	int _ID;

};

/**
 * Основной вид аффиксов в игре
 * Данный аффикс дает фиксированный бонус к характеристике персонажу
 * Класс содержит данные о типе характеристики, которая есть у персонажа и ее значение.
 */
UCLASS(Blueprintable)
class BROWSEPROJECT_API UBasicAffix : public UObject, public UAffix
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void Apply() override;

	UFUNCTION(BlueprintCallable)
	void Cancel() override;

	UFUNCTION(BlueprintCallable)
	FText GetText() override;

private:

};
