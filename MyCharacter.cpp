// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Gameframework/PlayerController.h"
#include "Animation/AnimInstance.h"
#include "Bot.h"
#include "EngineUtils.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 550.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	IsAlive = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetMovementSpeedAndAir();

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter::EndSprint);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction("Move", IE_Pressed, this, &AMyCharacter::Move);
}

void AMyCharacter::MoveForward(float Value)
{
	if (!IsAlive) return;
	if (Value != 0.0f && !bIsAttacking) {
		auto YawRotation = FRotator(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
		auto Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if (!IsAlive) return;

	if (Value != 0.0f && !bIsAttacking) {
		auto YawRotation = FRotator(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
		auto Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::Sprint()
{
	if (!IsAlive) return;
	if (bInAir) return;
	MovementState = EMovementState::MS_Sprinting;
	GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
}

void AMyCharacter::EndSprint()
{
	if (!IsAlive) return;
	if (GetCharacterMovement()->Velocity.Size() == 0) return;
	MovementState = EMovementState::MS_Normal;
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

void AMyCharacter::Jump()
{
	if (!IsAlive) return;
	if (bIsAttacking) return;

	Super::Jump();
}

void AMyCharacter::Move()
{
	for (TActorIterator<ABot> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		MyBot = Cast<ABot>(*ActorItr);
		if (MyBot) {
			UE_LOG(LogTemp, Warning, TEXT("Bot Found"));
			MyBot->MoveToDestination();
		}
	}
}

void AMyCharacter::SetMovementSpeedAndAir() {
	auto CharSpeed = GetVelocity();
	auto LateralSpeed = FVector(CharSpeed.X, CharSpeed.Y, 0.0f);

	MovementSpeed = LateralSpeed.Size();
	SprintingSpeed = LateralSpeed.Size() + 100.f;

	bInAir = GetMovementComponent()->IsFalling();
}

