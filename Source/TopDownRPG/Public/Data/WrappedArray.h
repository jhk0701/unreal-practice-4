// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template<typename T>
class TOPDOWNRPG_API FWrappedArray
{
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<T> Array;
};

template class FWrappedArray<FString>;