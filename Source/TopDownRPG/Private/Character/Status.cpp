// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Status.h"

Status::Status(uint32 InitMaxValue) : 
	MaxValue(InitMaxValue),
	CurValue(MaxValue)
{
}

Status::Status(uint32 InitMaxValue, uint32 InitCurrentValue) : 
	MaxValue(InitMaxValue),
	CurValue(InitCurrentValue)
{
}

Status::~Status(){}

uint32 Status::Add(uint32 Value)
{
	CurValue = FMath::Min(CurValue + Value, MaxValue);
	OnValueChanged.Broadcast(MaxValue, CurValue);

	return CurValue;
}

uint32 Status::Subtract(uint32 Value)
{
	if (CurValue < Value)
		Value = CurValue;

	CurValue -= Value;
	OnValueChanged.Broadcast(MaxValue, CurValue);
	return CurValue;
}

bool Status::TrySubtract(uint32 Value)
{
	if (CurValue < Value)
		return false;

	Subtract(Value);
	return true;
}

void Status::ChangeMaxValue(uint32 NewMaxValue)
{
	MaxValue = NewMaxValue;
	CurValue = NewMaxValue;

	OnValueChanged.Broadcast(NewMaxValue, NewMaxValue);
}

void Status::ChangeMaxValue(uint32 NewMaxValue, uint32 NewCurValue)
{
	MaxValue = NewMaxValue;
	CurValue = NewCurValue;

	OnValueChanged.Broadcast(NewMaxValue, NewCurValue);
}
