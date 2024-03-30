// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BrowseProject/ItemSystem/ItemEnums.h"
#include "BrowseProject/Components/FunctionalityComponentsInterface.h"
#include "PlayableCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class BROWSEPROJECT_API APlayableCharacter : public ACharacter, public IFunctionalityComponents
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	APlayableCharacter();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Components", meta = (DisplayName = "Inventory Component", AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryComponent> _InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Components", meta = (DisplayName = "Character Parts List", AllowPrivateAccess = "true"))
	TMap<ESlotType, TObjectPtr<USkeletalMeshComponent>> _CharacterParts;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Components", meta = (DisplayName = "Spring Arm", AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> _SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Components", meta = (DisplayName = "Camera Component", AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> _CameraComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Объявление методов интерфейса Functionality Components
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UInventoryComponent* GetInventoryComponent();
};
