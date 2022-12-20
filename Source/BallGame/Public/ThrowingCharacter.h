// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThrowingCharacter.generated.h"

class UBillboardComponent;
class ABall;
class UPhysicsHandleComponent;

UCLASS()
class BALLGAME_API AThrowingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Constructor */
	AThrowingCharacter();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	
public:	
	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	/** Called when we press left mouse button. */
	void StartShootBall();

	/** Called when we release left mouse button. */
	void StopShootBall();

	/** Shoots the ball in direction of the forward vector of the ball. */
	void ShootBall();

	/** Spawns a new ball and grabs it, meaning attaches it to the physics handle. */
	void SpawnAndGrabBall();

	/** Called when the shooting strength is updated. */
	UFUNCTION(BlueprintImplementableEvent)
	void ShootingStrengthUpdated(float ShootingTime);
	
	
	/** The blueprint class of the ball we are spawning. */
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABall> BallClass; 

private: 
	/** Stores the ball we are currently holding. If nullptr, we are not holding a ball. */
	ABall* Ball;

	// The billboard component we use to determine the location and rotation of the ball we are holding. */
	UBillboardComponent* Billboard;
	
	/** The physics handle where we attach the ball: */
	UPhysicsHandleComponent* PhysicsHandle;
	
public: 
	/** A multiplier to tweak the impulse the ball is thrown with. */
	UPROPERTY(EditAnywhere)
	float ForceMultiplier = 100000.f;

	/** The time to respawn the ball in seconds. */
	UPROPERTY(EditAnywhere)
	float RespawnTime = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxShootingTime = 3.f;
	
private:
	/** The time we were trying to shoot the ball in seconds  */
	float ShootingTime = 0.0f;

	/** The strength of the impulse we shoot the ball with */
	float ShootingStrength = 0.0f; 
	
	/** If the player is currently shooting, meaning they have the left mouse button clicked. */
	bool bIsShooting = false; 

	

	

	
};
