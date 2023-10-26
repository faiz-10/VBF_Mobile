// Fill out your copyright notice in the Description page of Project Settings.



#include "LobbyPlayerController.h"
#include "Kismet/GameplayStatics.h"

void ALobbyPlayerController::LoadInfo()
{
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	LoadedDelegate.BindUObject(this, &ALobbyPlayerController::LoadedGameDelegateFunction);
	UGameplayStatics::AsyncLoadGameFromSlot("Slot_Name", 0, LoadedDelegate);
}

void ALobbyPlayerController::LoadedGameDelegateFunction(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	
}
