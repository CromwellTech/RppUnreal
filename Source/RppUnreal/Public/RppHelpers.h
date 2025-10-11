// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "observables/observable.hpp"

/**
 * 
 */
class RPPUNREAL_API RppHelpers
{
public:
	static auto TakeWhileNotNull(auto* Self)
	{
		return rpp::ops::take_while([Self](auto Input) { return Self != nullptr; });
	}
};
