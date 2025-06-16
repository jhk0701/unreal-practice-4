// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Function/BuffAbilityFunc.h"

inline uint32 UBuffAbilityFunc::Operate(uint32 Object, uint32 Value)
{
	uint32 Result = Object;

	switch (OperType)
	{
	case EOperateType::Addictive:
		Result += Value;
		break;
	case EOperateType::Multiply:
		Result *= Value;
		break;
	case EOperateType::Override:
		Result = Value;
		break;
	default: // Addictive
		Result += Value;
		break;
	}

	return Result;
}

void UBuffAbilityFunc::Operate(AActor* Object, uint32 Value)
{
	return;
}
