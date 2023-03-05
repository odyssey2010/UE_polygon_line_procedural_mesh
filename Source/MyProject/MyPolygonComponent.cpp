// Copyright www.3dcodekits.com, 2023
// Author: devx.3dcodekits.com@gmail.com

#include "MyPolygonComponent.h"

// Sets default values for this component's properties
UMyPolygonComponent::UMyPolygonComponent(const FObjectInitializer& ObjectIn) :
	UProceduralMeshComponent(ObjectIn)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Disable lighting effects
	bAffectDistanceFieldLighting = false;
	bAffectDynamicIndirectLighting = false;

	static FString Path = TEXT("/Game/M_LineMaterial");
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialLoader(*Path);

	if (MaterialLoader.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load material at path: %s"), *Path);

		Material = MaterialLoader.Object;
	}
}

void UMyPolygonComponent::PostLoad()
{
	Super::PostLoad();

	BuildMesh();	
}

void UMyPolygonComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property) 
	{
		BuildMesh();
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

// Called when the game starts
void UMyPolygonComponent::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void UMyPolygonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyPolygonComponent::BuildMesh()
{
	TArray<FVector> Vertices;
	TArray<FLinearColor> Colors;
	TArray<FVector> Normals;
	TArray<int32> Triangles;

	FVector Point, DirVert, DirHorz; // Direction Up, Out
	FVector V0, V1, V2, V3;
	FVector LastV0, LastV1, LastV2, LastV3;
	int32 I0, I1, I2, I3;
	int32 LastI0, LastI1, LastI2, LastI3;
	float SinTheta, CosTheta, Theta;
	const float UnitSize = 0.05f;	// Half size of unit 0.1f 

	for (uint32 i = 0; i <= Side; ++i)
	{
		Theta = FMath::DegreesToRadians(i * 360.0f / Side);
		FMath::SinCos(&SinTheta, &CosTheta, Theta);

		Point = FVector(SinTheta * Radius, CosTheta * Radius, 0.0f);
		DirVert = FVector(0.0f, 0.0f, 1.0f);
		DirHorz = FVector(SinTheta, CosTheta, 0.0f);

		V0 = Point + DirHorz * UnitSize;
		V1 = Point + DirHorz * -UnitSize;
		V2 = Point + DirVert * UnitSize;
		V3 = Point + DirVert * -UnitSize;

		I0 = Vertices.Add(V0);
		I1 = Vertices.Add(V1);
		I2 = Vertices.Add(V2);
		I3 = Vertices.Add(V3);

		Normals.Add(DirHorz);
		Normals.Add(- DirHorz);
		Normals.Add(DirVert);
		Normals.Add(-DirVert);

		Colors.Add(Color);
		Colors.Add(Color);
		Colors.Add(Color);
		Colors.Add(Color);
				
		if (i > 0)	// Generate triangles except first index
		{
			Triangles.Add(LastI0); Triangles.Add(I0), Triangles.Add(I1);
			Triangles.Add(I1), Triangles.Add(LastI1), Triangles.Add(LastI0);

			Triangles.Add(LastI2); Triangles.Add(I2), Triangles.Add(I3);
			Triangles.Add(I3), Triangles.Add(LastI3), Triangles.Add(LastI2);
		}

		LastV0 = V0;
		LastV1 = V1;
		LastV2 = V2;
		LastV3 = V3;

		LastI0 = I0;
		LastI1 = I1;
		LastI2 = I2;
		LastI3 = I3;
	}

	CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, TArray<FVector2D>(), Colors, TArray<FProcMeshTangent>(), false);

	if (MaterialInstanceDynamic == nullptr)
	{
		MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(Material, this);
	}

	MaterialInstanceDynamic->SetScalarParameterValue("Thickness", Thickness);
	SetMaterial(0, MaterialInstanceDynamic);
}