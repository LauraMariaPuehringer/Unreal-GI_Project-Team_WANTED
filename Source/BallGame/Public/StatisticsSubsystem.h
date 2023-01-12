// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StatisticsSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FMovingCubeInformation
{
	GENERATED_USTRUCT_BODY()

	/** The size of the cube. */ 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Size;

	/** The velocity of the cube in UE units/s. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity;
	
	/* The distance of the cube to the player camera when the cube was spawned. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitialDistanceToPlayer;

	/** The distance of the cube to the player camera when the cube was shot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShotDistanceToPlayer;

	/** The number of attempts that failed before the cube was shot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumFailedAttempts;

	/** The time passed from the cube being spawned until the cube being shot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeUntilShot;

	/** Returns a string containing the struct in the format of a CSV line. */
	FString ToCSVLine();

	/** Returns the matching CSV headline to the struct. */
	static FString ToCSVHeadline(); 

};

/**
 * Actor that handles storing a statistics file. 
 */
UCLASS()
class BALLGAME_API UStatisticsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	/** Sets defaults. */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	/** Creates new file with given ID and writes all stored cube information to it. */
	UFUNCTION(BlueprintCallable)
	void WriteCachedCubeInfo(UPARAM(ref) FString& ID);

	/** Caches cube data so it can be written later when finished. */
	UFUNCTION(BlueprintCallable)
	void CacheCubeInfo(UPARAM(ref) FMovingCubeInformation& CubeInfo); 

	/** Sets the filepath where the statistics file is stored. */
	UFUNCTION(BlueprintSetter)
	void SetFilePath(FString Path);

	/** The filepath for the CSV file we want to store. */
	FString FilePath;

	/** Stores the content that will be written to the file. */
	FString Content; 
};


