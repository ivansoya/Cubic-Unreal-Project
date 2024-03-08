// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AffixesData.h"
#include "Affixes.generated.h"

/**
 * ����������� ����� ���� ��������.
 * �������� ����� ������ �������, ������� ���������� �������������� � ����������� �������
 */
class BROWSEPROJECT_API UAffix
{

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Affix Description on Item"))
	FText Description;

public: 

	/// <summary>
	/// ������� ��� ���������� ������� �� ���������
	/// </summary>
	/// <returns></returns>
	virtual void Apply() = 0;

	/// <summary>
	/// ������� ��� ������ ������� �� ���������
	/// </summary>
	/// <returns></returns>
	virtual void Cancel() = 0;

	/// <summary>
	/// ������� ���������� ����� �������� �������
	/// </summary>
	/// <returns>����� ��������</returns>
	virtual FText GetText() = 0;

private:

	UPROPERTY(VisibleAnywhere, Meta = (DisplayName = "Affix ID"))
	int _ID;

};

/**
 * �������� ��� �������� � ����
 * ������ ������ ���� ������������� ����� � �������������� ���������
 * ����� �������� ������ � ���� ��������������, ������� ���� � ��������� � �� ��������.
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
