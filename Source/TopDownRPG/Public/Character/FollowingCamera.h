// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FollowingCamera.generated.h"

UCLASS()
class TOPDOWNRPG_API AFollowingCamera : public AActor
{
	GENERATED_BODY()
	

protected:
	UPROPERTY()
	TObjectPtr<USceneComponent> root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent> springArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<AActor> followingTarget;

public:	
	AFollowingCamera();
	virtual void Tick(float DeltaTime) override;

	void SetTarget(AActor* target) { followingTarget = target; }

};
