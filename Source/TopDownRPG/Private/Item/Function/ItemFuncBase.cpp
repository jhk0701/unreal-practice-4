// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Function/ItemFuncBase.h"

FFunctionContext& UItemFuncBase::GetContext(uint32 InValue, float InDuration)
{
	FFunctionContext* Context = NewObject<FFunctionContext>();
	
	Context->Func = this;
	Context->Value = InValue;
	Context->Duration = InDuration;

	return *Context;
}
