// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnValueChanged, uint32, uint32);

class TOPDOWNRPG_API Status
{

public:
	Status(uint32 InitMaxValue);
	~Status();

	FOnValueChanged OnValueChanged;

	uint32 GetMaxValue() { return maxValue; }
	uint32 GetCurrentValue() { return curValue; }

	uint32 operator +(const uint32 Value)
	{
		curValue = FMath::Min(curValue + Value, maxValue);
		OnValueChanged.Broadcast(curValue, maxValue);
		return curValue;
	}

	uint32 operator -(const uint32 Value)
	{
		curValue = FMath::Max(curValue - Value, uint32(0));
		OnValueChanged.Broadcast(curValue, maxValue);
		return curValue;
	}


private:
	uint32 maxValue;
	uint32 curValue;

};
