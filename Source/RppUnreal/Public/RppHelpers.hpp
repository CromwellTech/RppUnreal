#pragma once
#include "observables/observable.hpp"

class RppHelpers
{
public:
	static auto TakeWhileNotNull(auto* Self)
	{
		return rpp::ops::take_while([Self](auto Input) { return Self != nullptr; });
	}
};
