// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "TargetInfoBar.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BROWSEPROJECT_API UTargetInfoBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, DisplayName = "Target Name"))
	TObjectPtr<UTextBlock> TargetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, DisplayName = "Target Level"))
	TObjectPtr<UTextBlock> TargetLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, DisplayName = "Target Max Health"))
	TObjectPtr<UTextBlock> TargetMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, DisplayName = "Target Current Health"))
	TObjectPtr<UTextBlock> TargetCurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, DisplayName = "Target Max Durability"))
	TObjectPtr<UTextBlock> TargetMaxDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, DisplayName = "Target Current Durability"))
	TObjectPtr<UTextBlock> TargetCurrentDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, DisplayName = "Target HP Bar"))
	TObjectPtr<UProgressBar> TargetHpBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, DisplayName = "Target Durability Bar"))
	TObjectPtr<UProgressBar> TargetDurabilityBar;

protected:



};
