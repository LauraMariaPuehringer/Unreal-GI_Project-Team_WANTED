// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingCube.h"

// Sets default values
AMovingCube::AMovingCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingCube::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnPosition = GetActorLocation();

	// Set the size of the cube
	CubeMesh = FindComponentByClass<UStaticMeshComponent>();
	CubeMesh->SetWorldScale3D(CubeSize);

	// Bind the OnCompHit function to the OnComponentHit event of the cube. This means it is called each time, when the ball hits another component. 
	CubeMesh->OnComponentHit.AddDynamic(this, &AMovingCube::OnCompHit);
}

// Called every frame
void AMovingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Store current position and add the cube's velocity.
	// Notice that we multiply it with our delta time to make sure the velocity of the ball remains frame rate independent!
	FVector CurrentPosition = GetActorLocation();
	FVector NewPosition = CurrentPosition + CubeVelocity * DeltaTime;
	SetActorLocation(NewPosition, true);

	// Calculate the distance between the current position and the start position
	// When the distance is larger than the max distance, we switch directions.
	float DistanceMoved = FVector::Dist(NewPosition, SpawnPosition);
	if (DistanceMoved > MaxDistance)
	{
		CubeVelocity = -CubeVelocity;
	}
}

void AMovingCube::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ABall* HitActor = Cast<ABall>(OtherActor);

	if (HitActor != nullptr)
	{
		// Trigger hit event
		HitByBall();

		// Destroy the cube when it was hit
		Destroy();
	}
	
}

