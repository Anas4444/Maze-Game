// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Bot.generated.h"

class USphereComponent;
class UBoxComponent;
class AMyCharacter;
class ATargetPoint;
class AAIController;
class ADetectiveVsPrisonerGameModeBase;

UCLASS()
class DETECTIVEVSPRISONER_API ABot : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		USphereComponent* DetectSphere;
	
	UPROPERTY(EditAnywhere)
		USphereComponent* CombatSphere;
	
	UPROPERTY(EditAnywhere)
		UBoxComponent* AttackHitBoxLeft;
	
	UPROPERTY(EditAnywhere)
		UBoxComponent* AttackHitBoxRight;
	
	UFUNCTION()
		virtual void DetectSphereOnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
		virtual void DetectSphereOnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		virtual void CombatSphereOnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
		virtual void CombatSphereOnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
		virtual void AttackHitBoxOnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult & SweepResult);

	AMyCharacter* TargetChar;
	ADetectiveVsPrisonerGameModeBase* GM;

	AAIController* AI_Controller;

	void MoveToTarget();

	void MoveToPoint();

	void MoveToDestination();

	/*UFUNCTION()
		void Movement(int index);*/

	UPROPERTY(BlueprintReadOnly)
		bool IsAlive = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bAttacking;
	
	UPROPERTY(EditAnywhere)
		float MoveToTargetRadius = 10.0f;

};
