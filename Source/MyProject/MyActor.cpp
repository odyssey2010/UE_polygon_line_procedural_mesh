// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "MyPolygonComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PolygonComponent = CreateDefaultSubobject<UMyPolygonComponent>(TEXT("PolygonComponent"));
	PolygonComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rotation = GetActorRotation();

	Rotation.Roll += RotationSpeed.X * DeltaTime;	
	Rotation.Pitch += RotationSpeed.Y * DeltaTime;	
	Rotation.Yaw += RotationSpeed.Z * DeltaTime;
	
	SetActorRotation(Rotation);	
}

