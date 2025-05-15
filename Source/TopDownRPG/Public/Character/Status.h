// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnValueChanged, uint32, uint32);

class TOPDOWNRPG_API Status
{

public:
	Status(uint32 InitMaxValue);
	Status(uint32 InitMaxValue, uint32 InitCurrentValue);
	~Status();

	FOnValueChanged OnValueChanged;

	uint32 GetMaxValue() { return maxValue; }
	uint32 GetCurrentValue() { return curValue; }

	uint32 Add(uint32 Value);
	uint32 Subtract(uint32 Value);
	bool TrySubtract(uint32 Value);

	void ChangeMaxValue(uint32 Value);

private:
	const uint32 zero = 0;
	uint32 maxValue;
	uint32 curValue;

};
