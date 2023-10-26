// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameInfo.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VBF_MOBILE_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void LoadInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LoadedName;

	void LoadedGameDelegateFunction(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);
};
