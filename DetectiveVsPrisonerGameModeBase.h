// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
//#include <vector>
#include "Search.cpp"
#include "DetectiveVsPrisonerGameModeBase.generated.h"

/**
 * 
 */

class ATargetPoint;
class ABot;
class AActor;

UCLASS()
class DETECTIVEVSPRISONER_API ADetectiveVsPrisonerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		ADetectiveVsPrisonerGameModeBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<ATargetPoint> Point;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> OtherPoint;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Obstacle;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Bot;

	UPROPERTY(EditAnywhere)
		int mapL;
	
	UPROPERTY(EditAnywhere)
		int mapW;
	
	int L;
	int W;
	int NavHeight;
	int NavWidth;

	void IncrementL();
	
	std::vector<ATargetPoint*> NavigationAreas;
	std::vector<FVector> Navigation;
	Maze<std::tuple<int, int>, FString>* maze;
	
	void SpawnTargetPoint();

	void SpawnWalls();

	void GenerateMap();

	void SetupNavigationAreas();

	void SetupNavigation();

	int GetLocationIndex();
	
};
