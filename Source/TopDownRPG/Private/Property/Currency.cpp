// Fill out your copyright notice in the Description page of Project Settings.


#include "Property/Currency.h"

Currency::Currency() : Value(0)
{
}

Currency::Currency(uint32 InValue) : Value(InValue)
{
}

Currency::~Currency()
{
}

void Currency::Add(uint32 InValue)
{	
	Value += InValue;

	OnValueChanged.Broadcast(Value);
}

bool Currency::SafeSub(uint32 InValue)
{
	if(Value - InValue < 0)
		return false;

	Value -= InValue;
	OnValueChanged.Broadcast(Value);

	return true;
}
