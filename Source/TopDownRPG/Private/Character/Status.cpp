// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Status.h"

FStatus::FStatus(uint32 InitMaxValue) :
	MaxValue(InitMaxValue),
	CurValue(MaxValue)
{
}

FStatus::FStatus(uint32 InitMaxValue, uint32 InitCurrentValue) :
	MaxValue(InitMaxValue),
	CurValue(InitCurrentValue)
{
}

FStatus::~FStatus(){}

uint32 FStatus::Add(uint32 Value)
{
	CurValue = FMath::Min(CurValue + Value, MaxValue);
	OnValueChanged.Broadcast(MaxValue, CurValue);

	return CurValue;
}

uint32 FStatus::Subtract(uint32 Value)
{
	if (CurValue < Value)
		Value = CurValue;

	CurValue -= Value;
	OnValueChanged.Broadcast(MaxValue, CurValue);
	return CurValue;
}

bool FStatus::TrySubtract(uint32 Value)
{
	if (CurValue < Value)
		return false;

	Subtract(Value);
	return true;
}

void FStatus::ChangeMaxValue(uint32 NewMaxValue)
{
	MaxValue = NewMaxValue;
	CurValue = NewMaxValue;

	OnValueChanged.Broadcast(NewMaxValue, NewMaxValue);
}

void FStatus::ChangeMaxValue(uint32 NewMaxValue, uint32 NewCurValue)
{
	MaxValue = NewMaxValue;
	CurValue = NewCurValue;

	OnValueChanged.Broadcast(NewMaxValue, NewCurValue);
}
