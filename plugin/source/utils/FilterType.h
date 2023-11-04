#pragma once

#include "BinaryData.h"
#include "JuceHeader.h"
#include <functional>
#include "utils/SVGData.h"

class FilterType
{
  public:
	enum Value
	{
		firstValue,
		LOWPASS = firstValue,
		BANDPASS,
		HIGHPASS,
		lastValue = HIGHPASS
	};

	static juce::String toString(FilterType::Value filterType)
	{
		switch (filterType)
		{
		case FilterType::LOWPASS:
			return "Lowpass";
		case FilterType::BANDPASS:
			return "Bandpass";
		case FilterType::HIGHPASS:
			return "Highpass";
		default:
			jassertfalse;
			return "Should not happen";
		}
	}

	static SVGData getSVG(FilterType::Value filterType)
	{
		switch (filterType)
		{
		case FilterType::LOWPASS:
			return SVGData{BinaryData::lowpass_svg, BinaryData::lowpass_svgSize};
		case FilterType::BANDPASS:
			return SVGData{BinaryData::bandpass_svg, BinaryData::bandpass_svgSize};
		case FilterType::HIGHPASS:
			return SVGData{BinaryData::highpass_svg, BinaryData::highpass_svgSize};
		default:
			jassertfalse;
			/* return "Should not happen"; */
		}
	}

	static juce::Array<FilterType::Value> toArray()
	{
		juce::Array<FilterType::Value> filterTypeArray;
		for (int i = ( int ) FilterType::firstValue; i <= ( int ) FilterType::lastValue; i++)
		{
			auto tmp = FilterType::fromInt(i);
			filterTypeArray.add(tmp);
		}
		return filterTypeArray;
	}

	static juce::StringArray toStringArray()
	{
		juce::StringArray filterTypeStringArray;

		for (auto type : FilterType::toArray())
		{
			filterTypeStringArray.add(toString(type));
		}

		return filterTypeStringArray;
	}

	static juce::dsp::StateVariableTPTFilterType getFilterType(FilterType::Value filterType)
	{
		switch (filterType)
		{
		case FilterType::LOWPASS:
			return juce::dsp::StateVariableTPTFilterType::lowpass;
		case FilterType::BANDPASS:
			return juce::dsp::StateVariableTPTFilterType::bandpass;
		case FilterType::HIGHPASS:
			return juce::dsp::StateVariableTPTFilterType::highpass;
		default:
			jassertfalse;
			return juce::dsp::StateVariableTPTFilterType::lowpass;
		}
	}

	FilterType() = delete;

	constexpr FilterType(Value aType) : value(aType)
	{
	}

	constexpr operator Value() const
	{
		return value;
	}

	explicit operator bool() const = delete;

	constexpr bool operator==(FilterType a) const
	{
		return value == a.value;
	}

	constexpr bool operator!=(FilterType a) const
	{
		return value != a.value;
	}

	static Value fromInt(int i)
	{
		jassert(i >= static_cast<int>(FilterType::firstValue) && i <= static_cast<int>(Value::lastValue));
		return static_cast<Value>(i);
	}

  private:
	Value value;
};
