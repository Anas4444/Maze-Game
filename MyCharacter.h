// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ABot;

UENUM(BlueprintType)
enum class EMovementState : uint8 {
	MS_Normal UMETA(DisplayName = "Normal"),
	MS_Sprinting UMETA(DisplayName = "Sprinting")
};

UCLASS()
class DETECTIVEVSPRISONER_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void Sprint();
	void EndSprint();
	void Jump() override;
	void Move();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;

	UPROPERTY(BlueprintReadOnly)
		bool IsAlive;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EMovementState MovementState;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsAttacking;
	
	UPROPERTY(BlueprintReadOnly)
		bool bInAir;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float MovementSpeed;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float SprintingSpeed;
	
	void SetMovementSpeedAndAir();
	
	ABot* MyBot;
};
