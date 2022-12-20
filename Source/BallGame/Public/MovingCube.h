// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.h"
#include "MovingCube.generated.h"


UCLASS()
class BALLGAME_API AMovingCube : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Constructor */
	AMovingCube();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:	
	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Called when cube was hit by other component. */
	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
	/** The velocity of the cube. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	FVector CubeVelocity = FVector(100, 0, 0);

	/** The size of the cube */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	FVector CubeSize = FVector(1.0f, 1.0f, 1.0f);

	/** The distance the cube will move in each direction. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	float MaxDistance = 1000;

	/** Stores the position where the cube was spawned. */
	FVector SpawnPosition;

	/** Stores The cube mesh */
	UStaticMeshComponent* CubeMesh;

	/** Triggered when a cube was hit by a ball. */
	UFUNCTION(BlueprintImplementableEvent)
	void HitByBall();


};
