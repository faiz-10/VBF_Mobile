// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SaveGameInfo.h"
#include "Kismet/GameplayStatics.h"
#include "LoginPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VBF_MOBILE_API ALoginPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
		void SaveInfo(FString PlayerName);

	void SaveGameDelegateFunction(const FString& SlotName, const int32 UserIndex, bool Success);

};
