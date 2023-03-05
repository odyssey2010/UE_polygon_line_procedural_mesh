// Copyright www.3dcodekits.com, 2023
// Author: devx.3dcodekits.com@gmail.com

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "MyPolygonComponent.generated.h"

UCLASS(Blueprintable)
class MYPROJECT_API UMyPolygonComponent : public UProceduralMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyPolygonComponent(const FObjectInitializer& ObjectIn);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void PostLoad() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void BuildMesh();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	double Radius{ 100.0f };

	UPROPERTY(EditAnywhere)
	uint32 Side{ 32 };

	UPROPERTY(EditAnywhere)
	float Thickness{ 1.0f };

	UPROPERTY(EditAnywhere)
	FLinearColor Color { 1.0f, 1.0f, 1.0f, 1.0f };

protected:
	UMaterial* Material { nullptr };

	UMaterialInstanceDynamic* MaterialInstanceDynamic{ nullptr };
};
