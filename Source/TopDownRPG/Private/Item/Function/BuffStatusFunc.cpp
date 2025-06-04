// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Function/BuffStatusFunc.h"


inline uint32 UBuffStatusFunc::Operate(uint32 Object, uint32 Value)
{
	switch (OperType)
	{
	case EOperateType::Addictive:
		break;
	case EOperateType::Multiply:
		break;
	case EOperateType::Override:
		break;
	default: // Addictive
		break;
	}

	return uint32();
}
