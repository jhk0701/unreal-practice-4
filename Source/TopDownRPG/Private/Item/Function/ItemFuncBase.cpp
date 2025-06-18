// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Function/ItemFuncBase.h"
#include "Item/Function/FunctionContext.h"


FFunctionContext UItemFuncBase::GetContext(uint32 Value, float Duration)
{
    return FFunctionContext(this, Value, Duration);
}
