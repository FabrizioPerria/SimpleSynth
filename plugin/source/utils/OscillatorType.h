#pragma once

#include "JuceHeader.h"

class OscillatorType
{
  public:
	enum Value
	{
		firstValue,
		SINE = firstValue,
		SQUARE,
		SAW,
		lastValue = SAW
	};

	static juce::String toString(OscillatorType::Value oscillatorType)
	{
		switch (oscillatorType)
		{
		case OscillatorType::SINE:
			return "Sine";
		case OscillatorType::SQUARE:
			return "Square";
		case OscillatorType::SAW:
			return "Saw";
		default:
			jassertfalse;
			return "Should not happen";
		}
	}

	static juce::StringArray toStringArray()
	{
		juce::StringArray oscillatorTypeStringArray;
		for (int i = ( int ) OscillatorType::firstValue; i <= ( int ) OscillatorType::lastValue; i++)
		{
			auto tmp = OscillatorType::fromInt(i);
			oscillatorTypeStringArray.add(toString(tmp));
		}
		return oscillatorTypeStringArray;
	}

	OscillatorType() = delete;

	constexpr OscillatorType(Value aType) : value(aType)
	{
	}

	constexpr operator Value() const
	{
		return value;
	}

	explicit operator bool() const = delete;

	constexpr bool operator==(OscillatorType a) const
	{
		return value == a.value;
	}

	constexpr bool operator!=(OscillatorType a) const
	{
		return value != a.value;
	}

	static Value fromInt(int i)
	{
		jassert(i >= static_cast<int>(OscillatorType::firstValue) && i <= static_cast<int>(Value::lastValue));
		return static_cast<Value>(i);
	}

  private:
	Value value;
};
