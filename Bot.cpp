// Fill out your copyright notice in the Description page of Project Settings.


#include "Bot.h"

#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "AIModule/Classes/AIController.h"
#include "MyCharacter.h"
#include "Animation/AnimInstance.h" 
#include "EngineUtils.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DetectiveVsPrisonerGameModeBase.h"
#include "Engine/TargetPoint.h" 

// Sets default values
ABot::ABot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DetectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Detect Sphere"));
	DetectSphere->SetupAttachment(GetRootComponent());
	DetectSphere->InitSphereRadius(600.0f);

	CombatSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Combat Sphere"));
	CombatSphere->SetupAttachment(GetRootComponent());
	CombatSphere->InitSphereRadius(75.0f);

	AttackHitBoxLeft = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackHitBoxLeft"));
	AttackHitBoxLeft->SetupAttachment(GetMesh(), TEXT("HitBoxLeftSocket"));

	AttackHitBoxRight = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackHitBoxRight"));
	AttackHitBoxRight->SetupAttachment(GetMesh(), TEXT("HitBoxRightSocket"));

}

// Called when the game starts or when spawned
void ABot::BeginPlay()
{
	Super::BeginPlay();

	AI_Controller = Cast<AAIController>(GetController());
	GM = Cast<ADetectiveVsPrisonerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//DetectSphere->OnComponentBeginOverlap.AddDynamic(this, &ABot::DetectSphereOnBeginOverlap);
	//DetectSphere->OnComponentEndOverlap.AddDynamic(this, &ABot::DetectSphereOnEndOverlap);

	CombatSphere->OnComponentBeginOverlap.AddDynamic(this, &ABot::CombatSphereOnBeginOverlap);
	CombatSphere->OnComponentEndOverlap.AddDynamic(this, &ABot::CombatSphereOnEndOverlap);

	AttackHitBoxLeft->OnComponentBeginOverlap.AddDynamic(this, &ABot::AttackHitBoxOnBeginOverlap);
	AttackHitBoxRight->OnComponentBeginOverlap.AddDynamic(this, &ABot::AttackHitBoxOnBeginOverlap);
	
	
}

// Called every frame
void ABot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABot::DetectSphereOnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult & SweepResult)
{
	if (!IsAlive) return;

	AMyCharacter* MyChar = Cast<AMyCharacter>(OtherActor);
	if (MyChar) {
		TargetChar = MyChar;
		//MoveToTarget();
	}
}

void ABot::DetectSphereOnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsAlive) return;

	AMyCharacter* MyChar = Cast<AMyCharacter>(OtherActor);
	if (MyChar) {
		TargetChar = nullptr;
		if (AI_Controller) AI_Controller->StopMovement();
	}
}

void ABot::CombatSphereOnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult & SweepResult)
{
	
}

void ABot::CombatSphereOnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ABot::AttackHitBoxOnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult & SweepResult)
{
	
}

void ABot::MoveToTarget()
{
	if (bAttacking) return;
	if (AI_Controller) {

		FNavPathSharedPtr NavPath;
		FAIMoveRequest MoveRequest;

		MoveRequest.SetGoalActor(TargetChar);
		MoveRequest.SetAcceptanceRadius(MoveToTargetRadius);

		AI_Controller->MoveTo(MoveRequest, &NavPath);
	}
}

void ABot::MoveToPoint() {
	if (AI_Controller) {
		ATargetPoint* p = Cast<ATargetPoint>(GM->NavigationAreas[GM->L]);
		float X = p->GetActorLocation().X;
		float Y = p->GetActorLocation().Y;
		float Z = p->GetActorLocation().Z;
		//if (X==500.0f) p->SetActorLocation(FVector(X+500.0f, Y, p->GetActorLocation().Z), false, 0, ETeleportType::None);
		//UE_LOG(LogTemp, Warning, TEXT("(%f, %f)"), X, Y);
		if (p)
		{
			FNavPathSharedPtr NavPath;
			FAIMoveRequest MoveRequest;

			MoveRequest.SetGoalActor(p);
			MoveRequest.SetAcceptanceRadius(0.0f);

			AI_Controller->MoveToActor(p, 0.0f, false);
			//AI_Controller->MoveTo(MoveRequest, &NavPath);
			//AI_Controller->MoveToLocation(FVector(X, Y, Z), 0.0f, false, true, true, false, false);
		}
		GM->IncrementL();
	}
}

void ABot::MoveToDestination()
{
	/*AI_Controller->MoveToLocation(GM->Navigation[GM->GetLocationIndex()], 0.0f);
	GM->IncrementL();*/
	if (AI_Controller) {
		if (GM->GetLocationIndex()==-1) return;
		AI_Controller->MoveToLocation(GM->Navigation[GM->GetLocationIndex()], 0.0f);
		GM->IncrementL();
		/*FTimerHandle MoveTimer;
		FTimerDelegate TimerDel;*/
		//TimerDel.BindUFunction(this, FName("Movement", index));
		//GetWorld()->GetTimerManager().SetTimer(MoveTimer, TimerDel, 0.1f, false);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), AI_Controller->GetMoveStatus());
		/*UE_LOG(LogTemp, Warning, TEXT("(%d, %d)"), GM->NavHeight, GM->NavWidth);
		if (AI_Controller->GetMoveStatus() == EPathFollowingStatus::Idle)
			AI_Controller->MoveToLocation(GM->Navigation[0]);*/
		//GetWorldTimerManager().SetTimer(MoveTimer, this, &ABot::Movement, 2.0f);
		//for (int i=0; i<10*10; i++) {
				//UE_LOG(LogTemp, Warning, TEXT("Moving"));
			/*for (int i=0; i<10*10;) {
				if (AI_Controller->GetMoveStatus() == EPathFollowingStatus::Moving) {
					UE_LOG(LogTemp, Warning, TEXT("Moving"));
					//break;
				}
				else {
					UE_LOG(LogTemp, Warning, TEXT("Idle"));
					i++;
				}
			}*/
				/*if (AI_Controller->GetMoveStatus() != EPathFollowingStatus::Moving)
				{
					AI_Controller->StopMovement();
					AI_Controller->MoveToLocation(GM->Navigation[i], 0.0f);
				}*/
				//if (AI_Controller) AI_Controller->StopMovement();
				//AI_Controller->MoveToLocation(GM->Navigation[x + y * 10], 0.0f);
		//}
		
		/*UE_LOG(LogTemp, Warning, TEXT("(%f, %f)"), GM->Navigation[GM->L].X, GM->Navigation[GM->L].Y);
		AI_Controller->MoveToLocation(GM->Navigation[GM->L], 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("(%f, %f)"), this->GetActorLocation().X, this->GetActorLocation().Y);
		GM->IncrementL();*/
	}
}

/*void ABot::Movement(int index)
{
	if (AI_Controller) {
		AI_Controller->StopMovement();
		AI_Controller->MoveToLocation(GM->Navigation[index], 0.0f);
	}
}*/