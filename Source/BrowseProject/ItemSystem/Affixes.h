// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Affixes.generated.h"

/**
 * ����������� ����� ���� ��������.
 * �������� ����� ������ �������, ������� ���������� �������������� � ����������� �������
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
 * �������� ��� �������� � ����
 * ������ ������ ���� ������������� ����� � �������������� ���������
 * ����� �������� ������ � ���� ��������������, ������� ���� � ��������� � �� ��������.
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

	// ����� ��� ���� �������������� ���������
	
	// ����� ��� �������� ��������������
};

/**
 * ������, ������� ���� ��������� ��������� ������
 * ����� �������� ������ �� �������
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
 * ������, ������� ���� ��������� ����������� ������, ������� ������������ ��� ����� ���� �������
 * ����� �������� ������ �� ������� � ������������ �������
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
