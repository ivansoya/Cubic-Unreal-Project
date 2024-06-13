// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrowseProject/Character/Interfaces/PickUp.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class APickUpCollider;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 * 
 */
UCLASS()
class BROWSEPROJECT_API AMainPlayerController : public APlayerController, public IPickUp
{
	GENERATED_BODY()

public:
	AMainPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;

	// ��������������� ������� ����������� PickUP
public:

	UFUNCTION(BlueprintNativeEvent)
	void PickUpItem(AWorldItem* PickUpCollider, FVector LocToMove);

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;

	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

	// ���������� ��� �������� ���������� ������� pick ����������
	APickUpCollider* CashedPickUpCollider;

private:
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed	
};
