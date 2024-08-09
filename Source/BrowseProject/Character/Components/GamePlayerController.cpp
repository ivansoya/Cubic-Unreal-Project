// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/LocalPlayer.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BrowseProject/Character/Interfaces/Stat.h"
#include "BrowseProject/UI/Targeting/TargetInfoBar.h"
#include "BrowseProject/Character/Utility/PickUpCollider.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;

	_OnDisplayTargetBar.AddDynamic(this, &AMainPlayerController::SetTargetInfo);
	_OnHideTargetBar.AddDynamic(this, &AMainPlayerController::HideTargetInfo);
}

void AMainPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

	// Назначение переменных
	TArray<TEnumAsByte<EObjectTypeQuery>> Channels = { OTQ_Pawn, OTQ_Collectibles } ;
	FHitResult HitResult;
	// Находим объекты под курсором 
	GetHitResultUnderCursorForObjects(Channels, true, HitResult);
	AActor* FoundedActor = HitResult.GetActor();
	const IStatInterface* CastingResult = Cast<IStatInterface>(FoundedActor);
	// Если не найден актер и нет цели, то ничего не делаем;
	if (CastingResult == nullptr && _Target == nullptr) {
		return;
	}
	// Если актер не найден, но была цель, то скрываем полоску хп
	else if (CastingResult == nullptr && _Target != nullptr) {
		//_OnHideTargetBar.
		// Вызываем ивент по скрытию полоски хп
		_OnHideTargetBar.Broadcast();
		_Target = nullptr;
	}
	// Если был найден объект
	else if (CastingResult != nullptr) {
		// Если цель такая же, как и найденный объект, то ничего не делаем
		if (_Target == FoundedActor) {
			return;
		}
		// Иначе, если цель отличается от найденного объекта или не было цели, то запускаем ивент на отображение полоски
		int32 MaxHealth, CurrentHealth;
		IStatInterface::Execute_GetCharacterHealth(FoundedActor, CurrentHealth, MaxHealth);
		int32 MaxDurability, CurrentDurability;
		IStatInterface::Execute_GetCharacterDurability(FoundedActor, CurrentDurability, MaxDurability);
		int32 MonsterLevel = IStatInterface::Execute_GetCharacterLevel(FoundedActor);
		FString MonsterName = IStatInterface::Execute_GetCharacterName(FoundedActor);

		const FTargetDisplayInfo DisplayInfo = FTargetDisplayInfo(
			MonsterName, MonsterLevel, MaxHealth, CurrentHealth, MaxDurability, CurrentDurability		
		);

		_OnDisplayTargetBar.Broadcast(DisplayInfo);

		_Target = FoundedActor;
	}


}

void AMainPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AMainPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AMainPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AMainPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AMainPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AMainPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AMainPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AMainPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AMainPlayerController::OnTouchReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMainPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AMainPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}

	// Уничтожение пик ап коллайдера, если такой существовал
	if (CashedPickUpCollider) {
		CashedPickUpCollider->Destroy();
		CashedPickUpCollider = nullptr;
	}
}

void AMainPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void AMainPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AMainPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

// ---------------------------------------------------------------
// Реализация функций ITargetInfo интерфейса
// ---------------------------------------------------------------

void AMainPlayerController::SetTargetInfo_Implementation(const FTargetDisplayInfo& TargetInfo)
{
	if (TargetInfoWidget == nullptr) return;

	// Назначение значений монстра к виджету полоски цели
	TargetInfoWidget->TargetName->SetText(FText::FromString(TargetInfo.TargetName));
	TargetInfoWidget->TargetLevel->SetText(FText::FromString(FString::FromInt(TargetInfo.TargetLevel)));
	TargetInfoWidget->TargetHpBar->SetPercent(TargetInfo.CurrentHealth / float(TargetInfo.MaxHealth));
	TargetInfoWidget->TargetHpBar->SetPercent(TargetInfo.CurrentHealth / float(TargetInfo.MaxHealth));

	TargetInfoWidget->TargetMaxHealth->SetText(FText::FromString(FString::FromInt(TargetInfo.MaxHealth)));
	TargetInfoWidget->TargetCurrentHealth->SetText(FText::FromString(FString::FromInt(TargetInfo.CurrentHealth)));

	TargetInfoWidget->TargetMaxDurability->SetText(FText::FromString(FString::FromInt(TargetInfo.MaxDurability)));
	TargetInfoWidget->TargetCurrentDurability->SetText(FText::FromString(FString::FromInt(TargetInfo.CurrentDurability)));

	TargetInfoWidget->SetVisibility(ESlateVisibility::Visible);
}

void AMainPlayerController::HideTargetInfo_Implementation()
{
	if (TargetInfoWidget == nullptr) return;

	TargetInfoWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AMainPlayerController::ChangeHealthValue_Implementation(int32 CurrentHealth, int32 MaxHealth)
{
	TargetInfoWidget->TargetHpBar->SetPercent(CurrentHealth / float(MaxHealth));

	TargetInfoWidget->TargetMaxHealth->SetText(FText::FromString(FString::FromInt(MaxHealth)));
	TargetInfoWidget->TargetCurrentHealth->SetText(FText::FromString(FString::FromInt(CurrentHealth)));
}

void AMainPlayerController::ChangeDurabilityValue_Implementation(int32 CurrentDurability, int32 MaxDurability)
{
	TargetInfoWidget->TargetHpBar->SetPercent(CurrentDurability / float(MaxDurability));

	TargetInfoWidget->TargetMaxDurability->SetText(FText::FromString(FString::FromInt(MaxDurability)));
	TargetInfoWidget->TargetCurrentDurability->SetText(FText::FromString(FString::FromInt(CurrentDurability)));
}

// ---------------------------------------------------------------
// Реализация функций Pick Up интерфейса
// ---------------------------------------------------------------

void AMainPlayerController::PickUpItem_Implementation(AWorldItem* WorldItem, FVector LocToMove)
{
	if (CashedPickUpCollider) {
		CashedPickUpCollider->Destroy();
	}

	FTransform SpawnT = FTransform(LocToMove);
	CashedPickUpCollider = GetWorld()->SpawnActorDeferred<APickUpCollider>(APickUpCollider::StaticClass(), SpawnT);
	CashedPickUpCollider->SetItem(WorldItem);
	CashedPickUpCollider->FinishSpawning(SpawnT);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, LocToMove);
}