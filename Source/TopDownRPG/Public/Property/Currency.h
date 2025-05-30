// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCyurrencyChanged, uint32 InValue);

class TOPDOWNRPG_API Currency
{
public:
	FOnCyurrencyChanged OnValueChanged;

protected:
	uint32 Value;

public:
	Currency();
	Currency(uint32 InValue);
	~Currency();

	inline const uint32 GetCurrency() { return Value; }
	void Add(uint32 InValue);
	bool SafeSub(uint32 InValue);

};
