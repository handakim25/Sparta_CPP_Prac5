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

	UPROPERTY(EditAnywhere, Meta=(ClampMin="0.001"))
	float MoveInterval = 1.0f;

	UPROPERTY(EditAnywhere, Meta=(ClampMin="1"))
	int StepCount = 10;

	FTimerHandle TimerHandle;

	void OnTimerHandler();

	UPROPERTY(EditAnywhere, Meta=(ClampMin="0", ClampMax="1"))
	float EventProbability = 0.5f;

private:
	// 현재 이동 횟수
	int moveCount = 0;	
	// 현재 위치
	FVector2D curPos;
	// 누적 이동 거리
	float totalDistance = 0.0f;
	// 현재 프레임 이동 거리
	float moveDistance = 0.0f;
	// 이벤트 발생 회수
	int eventCount = 0;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move();
	float GetMoveDistance();

	void TriggerEvent();
protected:
	float Distance(FVector2D p1, FVector2D p2);
	int Step();
};
