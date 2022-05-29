// Copyright Epic Games, Inc. All Rights Reserved.

#include "DetectiveVsPrisonerGameModeBase.h"
#include "GameFramework/Actor.h"
#include "EngineUtils.h"
#include "Bot.h"
#include <algorithm>
#include "Engine/TargetPoint.h"

ADetectiveVsPrisonerGameModeBase::ADetectiveVsPrisonerGameModeBase() {
    PrimaryActorTick.bCanEverTick = true;
}

void ADetectiveVsPrisonerGameModeBase::BeginPlay() {
    Super::BeginPlay();
    SetupNavigationAreas();
    SpawnWalls();
}

void ADetectiveVsPrisonerGameModeBase::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

}

void ADetectiveVsPrisonerGameModeBase::IncrementL()
{
    FRotator r = FRotator(0.0f, 0.0f, 0.0f);
    FVector v = FVector(Navigation[GetLocationIndex()].X, Navigation[GetLocationIndex()].Y, Navigation[GetLocationIndex()].Z+90);
    GetWorld()->SpawnActor(OtherPoint, &v, &r);
    L++;
}

void ADetectiveVsPrisonerGameModeBase::SpawnTargetPoint() {
    /*mapL = mapL*100;
    mapW = mapW*100;*/
    for (int i=(-1)*mapL + 500; i<mapL; i+=1000) {
        for (int j=(-1)*mapW + 500; j<mapW; j+=1000) {
            FVector p = FVector(i, j, 160.0f);
            FRotator r = FRotator(0.0f, 0.0f, 0.0f);
            GetWorld()->SpawnActor(Point, &p, &r);
            //GetWorld()->SpawnActor(OtherPoint, &p, &r);
        }
    }
}

void ADetectiveVsPrisonerGameModeBase::SpawnWalls()
{
    maze = new Maze<std::tuple<int, int>, FString>("maze1.txt");
    FRotator r = FRotator(0.0f, 0.0f, 0.0f);
    float x = std::get<0>(maze->start->state);
    float y = std::get<1>(maze->start->state);
    FVector va = FVector(Navigation[x + y * 10].X, Navigation[x + y * 10].Y, 170.f);
    GetWorld()->SpawnActor(Bot, &va, &r);
    maze->checkAll();
    for (int i=0; i<maze->width; i++) {
        for (int j=0; j<maze->height; j++) {
            if (maze->explored[i][j]<0) {
                //UE_LOG(LogTemp, Warning, TEXT("i=%d, j=%d"), i, j);
                FVector v = FVector(Navigation[i + j * 10].X, Navigation[i + j * 10].Y, Navigation[i + j * 10].Z);
                GetWorld()->SpawnActor(Obstacle, &v, &r);
            }
        }
    }
}

void ADetectiveVsPrisonerGameModeBase::SetupNavigationAreas()
{
    SetupNavigation();
	SpawnTargetPoint();
    L = 0; W = 0;
    for (TActorIterator<ATargetPoint> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
        ATargetPoint* TargetPt =  Cast<ATargetPoint>(*ActorItr);
		if (TargetPt) NavigationAreas.push_back(TargetPt);
    }

    /*std::sort(NavigationAreas.begin(), NavigationAreas.end(), 
    [](ATargetPoint* p1, ATargetPoint* p2) {
        float X1 = p1->GetActorLocation().X;
        float X2 = p2->GetActorLocation().X;
        return X1 < X2;
    });
    for (int x=0; x<10*10; x+=10) {
        std::sort(std::next(NavigationAreas.begin(), x), std::next(NavigationAreas.begin(), x+9), 
        [](ATargetPoint* p1, ATargetPoint* p2) {
            float Y1 = p1->GetActorLocation().Y;
            float Y2 = p2->GetActorLocation().Y;
            return Y1 < Y2;
        });
    }*/
    for (int y=0; y<10; y++) {
        //UE_LOG(LogTemp, Warning, TEXT("["));
        for (int x=0; x<10; x++) {
            float X = NavigationAreas[x + y * 10]->GetActorLocation().X;
            float Y = NavigationAreas[x + y * 10]->GetActorLocation().Y;
            //UE_LOG(LogTemp, Warning, TEXT("(%f, %f), "), X, Y);
        }
        //UE_LOG(LogTemp, Warning, TEXT("]"));
    }
}

void ADetectiveVsPrisonerGameModeBase::SetupNavigation()
{
    NavHeight = (mapL/10)*2;
    NavWidth = (mapW/10)*2;
    mapL = mapL*100;
    mapW = mapW*100;
    L = 1;
    for (int i=(-1)*mapL + 500; i<mapL; i+=1000) {
        for (int j=(-1)*mapW + 500; j<mapW; j+=1000) { Navigation.push_back(FVector(i, j, 90.0f)); }
    }
}

int ADetectiveVsPrisonerGameModeBase::GetLocationIndex()
{
    if (L == maze->solution.size()) return -1;
    int x = std::get<0>(maze->solution[L]->state);
    int y = std::get<1>(maze->solution[L]->state);
    UE_LOG(LogTemp, Warning, TEXT("(%d, %d)"), x, y);
    return x + y * 10;
}

