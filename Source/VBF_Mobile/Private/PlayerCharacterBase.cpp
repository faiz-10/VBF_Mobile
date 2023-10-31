// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"


// Sets default values
APlayerCharacterBase::APlayerCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	TPPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPPCamera"));

	CameraBoom->SetupAttachment(RootComponent);
	TPPCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);

	CameraBoom->TargetArmLength = 400.f;

	//CameraBoom->bUsePawnControlRotation = true;
	TPPCamera->bUsePawnControlRotation = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	MaxHealth = 200.f;
	CurrentHealth = MaxHealth;

}

void APlayerCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacterBase, CurrentHealth);
}

// Called when the game starts or when spawned
void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(UGameplayStatics::GetPlayerController(this, 0)->GetLocalPlayer())) {
		UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		InputSystem->AddMappingContext(IMC_Main, 1);
	}

}

void APlayerCharacterBase::PlayerMovement(const FInputActionValue &Value)
{
	FVector2D Input = Value.Get<FVector2D>();

	FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, Input.Y);
	AddMovementInput(RightDirection, Input.X);
}

void APlayerCharacterBase::PlayerSight(const FInputActionValue &Value)
{
	FVector2d Input = Value.Get<FVector2D>();
	AddControllerPitchInput(Input.X);
	AddControllerYawInput(Input.Y);
}

void APlayerCharacterBase::PlayerAttack(const FInputActionValue& Value)
{
	FVector StartPos = TPPCamera->GetComponentLocation();
	FVector EndPos = StartPos + TPPCamera->GetForwardVector() * 50000;
	TEnumAsByte<EObjectTypeQuery> TypesEnum {EObjectTypeQuery::ObjectTypeQuery3};
	TArray<TEnumAsByte<EObjectTypeQuery>> TargetActorType;
	TargetActorType.Add(TypesEnum);
	TArray<AActor*> ActorsToIgnore;
	FHitResult OutHitResult;
	UKismetSystemLibrary::LineTraceSingleForObjects(this, StartPos, EndPos, TargetActorType, 1, ActorsToIgnore, EDrawDebugTrace::Persistent,OutHitResult, 1);


}

void APlayerCharacterBase::OnRep_CurrHealth()
{
	OnHealthUpdate();
}

void APlayerCharacterBase::OnHealthUpdate()
{
	if (IsLocallyControlled()) {
		// Client Specific functionality
	}

	if (GetLocalRole() == ROLE_Authority) {
		// Server Specific functionality
	}

	// functionality that occurs on both
}

// Called every frame
void APlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* PlayerInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	PlayerInput->BindAction(IA_Look, ETriggerEvent::Triggered, this, &APlayerCharacterBase::PlayerSight);
	PlayerInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacterBase::PlayerMovement);
	PlayerInput->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &APlayerCharacterBase::PlayerAttack);

}

