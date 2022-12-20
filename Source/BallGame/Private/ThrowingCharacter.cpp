// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowingCharacter.h"
#include <Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h>
#include "Components/BillboardComponent.h"
#include "Ball.h"
#include "Components/SphereComponent.h"


AThrowingCharacter::AThrowingCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AThrowingCharacter::BeginPlay()
{
	Super::BeginPlay();

	Billboard = this->FindComponentByClass<UBillboardComponent>();
	PhysicsHandle = this->FindComponentByClass<UPhysicsHandleComponent>();
}

void AThrowingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsShooting)
	{
		// Update the time we hold the left mouse button 
		ShootingTime += DeltaTime;
		
		// We clamp ShootingTime at 3 (seconds) so we can't scale up the strength infinitely.
		ShootingTime = FMath::Min(ShootingTime, 3.f);	
		ShootingStrength = ForceMultiplier * ShootingTime;

		// Fire the event so that we can use it to update
		ShootingStrengthUpdated(MaxShootingTime);
	}

	if (Billboard != nullptr && PhysicsHandle != nullptr)
	{
		// Update the target of the physics handle to the billboard position and rotation. 
		PhysicsHandle->SetTargetLocationAndRotation(Billboard->GetComponentLocation(), Billboard->GetComponentRotation());

		// We need to wake the physics handle when it is done interpolating to the target. Otherwise it will get "stuck". 
		if (PhysicsHandle->GetGrabbedComponent() && !PhysicsHandle->GetGrabbedComponent()->RigidBodyIsAwake())
		{
			PhysicsHandle->GetGrabbedComponent()->SetSimulatePhysics(true);
		}
	}
}

void AThrowingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind start and stop shooting functions to our input events. 
	InputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AThrowingCharacter::StartShootBall);
	InputComponent->BindAction("PrimaryAction", IE_Released, this, &AThrowingCharacter::StopShootBall);
}

void AThrowingCharacter::StartShootBall()
{
	bIsShooting = true; 
}

void AThrowingCharacter::StopShootBall()
{
	if (Ball) ShootBall();

	// Set timer to spawn new ball
	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AThrowingCharacter::SpawnAndGrabBall, RespawnTime, false);

	bIsShooting = false; 
	ShootingTime = 0.0f;
	ShootingStrength = 0; 
}

void AThrowingCharacter::SpawnAndGrabBall()
{
	// Calc spawn position and spawn rotation; set spawn params
	const FVector SpawnPos = Billboard->GetComponentLocation();
	const FRotator SpawnRot = Billboard->GetComponentRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Spawn a new ball
	Ball = GetWorld()->SpawnActor<ABall>(BallClass, SpawnPos, SpawnRot, SpawnParams);

	if (Ball)
	{
		// Ensure simulation is running for all bodies in this component
		USphereComponent* BallMesh = Ball->FindComponentByClass<USphereComponent>();

		// Attach ball to physics handle
		PhysicsHandle->GrabComponentAtLocationWithRotation(BallMesh, "", Ball->GetActorLocation(), Ball->GetActorRotation());
	}
}

void AThrowingCharacter::ShootBall()
{
	// Detach the ball from the physics handle
	PhysicsHandle->ReleaseComponent();

	// Retrieve ball mesh 
	UStaticMeshComponent* BallMesh = Ball->FindComponentByClass<UStaticMeshComponent>();

	// Apply an impulse to the ball so it is thrown away by the physics system
	BallMesh->AddImpulse(GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector() * ShootingStrength);
	
	// Ball variable now stores nullptr because we are not holding the ball anymore
	Ball = nullptr;
	
}
