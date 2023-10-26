// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "PlayerCharacterBase.generated.h"

UCLASS()
class VBF_MOBILE_API APlayerCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UCameraComponent* TPPCamera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class USpringArmComponent* CameraBoom;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UInputAction* IA_Move;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UInputAction* IA_Look;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UInputMappingContext* IMC_Main;


	void PlayerMovement(const FInputActionValue& Value);
	void PlayerSight(const FInputActionValue &Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
