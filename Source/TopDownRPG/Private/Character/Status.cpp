// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Status.h"

Status::Status(uint32 InitMaxValue)
	: maxValue(InitMaxValue),
	curValue(maxValue)
{
}

Status::Status(uint32 InitMaxValue, uint32 InitCurrentValue)
	: maxValue(InitMaxValue),
	curValue(InitCurrentValue)
{
}

Status::~Status()
{
}

uint32 Status::Add(uint32 Value)
{
	curValue = FMath::Min(curValue + Value, maxValue);
	OnValueChanged.Broadcast(maxValue, curValue);
	return curValue;
}

uint32 Status::Subtract(uint32 Value)
{
	curValue = FMath::Max(curValue - Value, zero);
	OnValueChanged.Broadcast(maxValue, curValue);
	return curValue;
}

bool Status::TrySubtract(uint32 Value)
{
	if (curValue - Value < zero)
		return false;

	Subtract(Value);
	return true;
}

void Status::ChangeMaxValue(uint32 Value)
{
	maxValue = Value;
	curValue = maxValue;

	OnValueChanged.Broadcast(maxValue, curValue);
}
