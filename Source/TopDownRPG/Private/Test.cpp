// Fill out your copyright notice in the Description page of Project Settings.


#include "Test.h"
#include <UObject/SoftObjectPtr.h>

#include <Engine/AssetManager.h>
#include <Engine/StreamableManager.h>

// Sets default values
ATest::ATest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
}

// Called when the game starts or when spawned
void ATest::BeginPlay()
{
	Super::BeginPlay();
	
	UStaticMesh* loadedMesh = LoadSync();
	
	if (loadedMesh)
		MainMesh->SetStaticMesh(loadedMesh);
	
}

// Called every frame
void ATest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMesh* ATest::LoadSync()
{
	return LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
}

void ATest::LoadAsync()
{
	// 매니저 받기
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

	// 에셋 경로 변수 선언
	FSoftObjectPath AssetPath("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere");

	Streamable.RequestAsyncLoad(
		AssetPath, 
		FStreamableDelegate::CreateLambda([AssetPath, this]() 
		{
			UStaticMesh* loadedMesh = Cast<UStaticMesh>(AssetPath.ResolveObject());
			if (loadedMesh) 
			{
				this->MainMesh->SetStaticMesh(loadedMesh);
			}
		}));
}
