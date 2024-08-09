// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrowseProject/Character/Interfaces/PickUp.h"
#include "BrowseProject/UI/Targeting/TargetInfoInterface.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

#define OTQ_Pawn EObjectTypeQuery::ObjectTypeQuery3
#define OTQ_Collectibles EObjectTypeQuery::ObjectTypeQuery6
#define OTQ_Player EObjectTypeQuery::ObjectTypeQuery7

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class APickUpCollider;
class UTargetInfoBar;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 * 
 */
UCLASS()
class BROWSEPROJECT_API AMainPlayerController : public APlayerController, public IPickUp, public ITargetInfo
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (DisplayName = "Constructed Class Of Target Info Widget", AllowedClasses = "UTargetInfoBar"))
	UClass* TargetInfoWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (DisplayName = "Target Info Widget"))
	TObjectPtr<UTargetInfoBar> TargetInfoWidget;

public:
	// ----------------------------------------------------
	// Переопределение функций интейрфейса PickUP
	// ----------------------------------------------------

	UFUNCTION(BlueprintNativeEvent)
	void PickUpItem(AWorldItem* PickUpCollider, FVector LocToMove);

public:
	// ----------------------------------------------------
	// Переопределение функций интейрфейса ITargetInfo
	// ----------------------------------------------------

	UFUNCTION(BlueprintNativeEvent)
	void SetTargetInfo(const FTargetDisplayInfo& TargetInfo);

	UFUNCTION(BlueprintNativeEvent)
	void HideTargetInfo();

	UFUNCTION(BlueprintNativeEvent)
	void ChangeHealthValue(int32 CurrentHealth, int32 MaxHealth);

	UFUNCTION(BlueprintNativeEvent)
	void ChangeDurabilityValue(int32 CurrentDurability, int32 MaxDurability);

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;

	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime);

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

	// Переменная для хранения последнего создана pick коллайдера
	APickUpCollider* CashedPickUpCollider;

private:

	AActor* _Target;

	FVector CachedDestination;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Delegates", meta = (DisplayName = "On Display Target Bar", AllowPrivateAccess = "true"))
	FOnDisplayTargetBarSignature _OnDisplayTargetBar;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Delegates", meta = (DisplayName = "On Hide Target Bar", AllowPrivateAccess = "true"))
	FOnHideTargetBarSignature _OnHideTargetBar;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed	
};
