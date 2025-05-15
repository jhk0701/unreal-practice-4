// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Status.h"

Status::Status(uint32 InitMaxValue)
	: maxValue(InitMaxValue),
	curValue(maxValue)
{
}

Status::~Status()
{
}
