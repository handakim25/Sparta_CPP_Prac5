// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class PRAC5_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Meta=(ClampMin="0"))
	float MoveInterval = 1.0f;

	UPROPERTY(EditAnywhere, Meta=(ClampMin="1"))
	int StepCount = 10;

	FTimerHandle TimerHandle;

	void OnTimerHandler();

private:
	int moveCount = 0;	
	FVector2D curPos;
	float totalDistance = 0.0f;
	float moveDistance = 0.0f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move();
	int Step();

	float GetMoveDistance();
protected:
	float Distance(FVector2D p1, FVector2D p2);
};
