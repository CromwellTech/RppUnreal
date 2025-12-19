#pragma once
#include <subjects/behavior_subject.hpp>

template <typename T>
class readonly_behavior_subject
{
private:
	rpp::subjects::behavior_subject<T> subject;
	
	TOptional<rpp::composite_disposable_wrapper> disposable;

public:
	readonly_behavior_subject(T initial_value) : subject(initial_value)
	{
	}

	readonly_behavior_subject(rpp::subjects::behavior_subject<T> initial_value) : subject(initial_value)
	{
	}

	readonly_behavior_subject(auto observable, T initial_value) : subject(initial_value)
	{
		disposable.Emplace(observable.subscribe_with_disposable([this](const T value)
		{
			this->get_observer().on_next(value);
		}));
	}
	
	~readonly_behavior_subject()
	{
		if (disposable.IsSet())
		{
			disposable.GetValue().dispose();
		}
	}

	T get_value() const { return subject.get_value(); }

	auto get_observable() const { return subject.get_observable(); }

	auto get_disposable() const { return subject.get_disposable(); }

private:
	auto get_observer() const { return subject.get_observer(); }
};
