// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillEffectBase.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FSkillEvent, AActor*)

/// <summary>
/// 스킬 표현 및 충돌 처리 액터
/// </summary>
UCLASS()
class TOPDOWNRPG_API ASkillEffectBase : public AActor
{
	GENERATED_BODY()

public:
	FSkillEvent OnSkillStarted;
	FSkillEvent OnSkillHitted;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPrimitiveComponent> Collider;

	// TODO : 스킬 시각 효과
	// TODO : 스킬 효과음

public:	
	ASkillEffectBase();
	virtual void BeginPlay() override;
	virtual void Activate();

protected:
	UFUNCTION()
	virtual void OnBeginOverlapped(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

};
