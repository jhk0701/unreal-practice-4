// Fill out your copyright notice in the Description page of Project Settings.


#include "Property/Currency.h"

FCurrency::FCurrency() : Value(0)
{
}

FCurrency::FCurrency(uint32 InValue) : Value(InValue)
{
}

FCurrency::~FCurrency()
{
}

void FCurrency::Add(uint32 InValue)
{	
	Value += InValue;

	OnValueChanged.Broadcast(Value);
}

bool FCurrency::SafeSub(uint32 InValue)
{
	if (Value < InValue)
		return false;

	Value -= InValue;
	OnValueChanged.Broadcast(Value);

	return true;
}
