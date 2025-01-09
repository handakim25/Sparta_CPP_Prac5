// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

#include "Math/UnrealMathUtility.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Constructor에서는 프로퍼티 값을 읽지 못한다. BeginPlay로 이동
	// PrimaryActorTick.TickInterval = MoveInterval; 

	// static int constructor_count = 0;

	// 에디터에서 설정한 값을 생성자에서 적용할 수 없다.
	// 찾아본 결과로는 CDO를 생성해서 그것을 이용하기 때문이라고 한다.
	// 추측컨데, 직렬화된 데이터가 쓰이는 것은 생성자 이후인 것으로 생각된다.
	// 따라서 Tick Interval의 초기화는 직렬화 이후 시점으로 해야 한다.

	// if(HasAnyFlags(RF_ClassDefaultObject))
	// {
	// 	UE_LOG(LogTemp, Log, TEXT("THIS IS CDO"));
	// }

	// UE_LOG(LogTemp, Log, TEXT("{%d} Constructor!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"), constructor_count++);
	// UE_LOG(LogTemp, Log, TEXT("Move Interval : %f"), MoveInterval);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/gameplay-timers-in-unreal-engine
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyActor::OnTimerHandler, MoveInterval, true, 0.0f);
}

void AMyActor::OnTimerHandler()
{
	Move();
	float distance = GetMoveDistance();

	UE_LOG(LogTemp, Log, TEXT("%d Move : {%f}, {%f} - Move {%f}"), moveCount, curPos.X, curPos.Y, distance);

	TriggerEvent();

	if(moveCount == StepCount)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		UE_LOG(LogTemp, Log, TEXT("Move Done! Total distance : {%f}, Total event count : {%d}"), totalDistance, eventCount);
	}
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyActor::Move()
{
	FVector2D dt(Step(), Step());
	
	curPos += dt;

	moveCount++;
	moveDistance = Distance(FVector2D::Zero(), dt);
	totalDistance += moveDistance;
}

int AMyActor::Step()
{
    return FMath::RandRange(0, 1);
}

float AMyActor::GetMoveDistance()
{
    return moveDistance;
}

void AMyActor::TriggerEvent()
{
	float rate = FMath::FRand();

	// FRand : [0.0f, 1.0f], 1.0이어도 실행되므로 <=이지만, 0.0에서는 실행되면 안 되므로 다시 체크해야 한다.
	if(EventProbability > 0 && rate <= EventProbability)
	{
		UE_LOG(LogTemp, Log, TEXT("Event Triggered!"));
		eventCount++;
	}
}

float AMyActor::Distance(FVector2D p1, FVector2D p2)
{
	return FMath::Sqrt((p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y));
}
