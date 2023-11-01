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

	typedef struct SVGData
	{
		const char *svg;
		const size_t size;
	} SVGData;

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

	static SVGData getSVG(OscillatorType::Value oscillatorType)
	{
		switch (oscillatorType)
		{
		case OscillatorType::SINE:
			return SVGData{BinaryData::sine_svg, BinaryData::sine_svgSize};
		case OscillatorType::SQUARE:
			return SVGData{BinaryData::square_svg, BinaryData::square_svgSize};
		case OscillatorType::SAW:
			return SVGData{BinaryData::sawtooth_svg, BinaryData::sawtooth_svgSize};
		default:
			jassertfalse;
			/* return "Should not happen"; */
		}
	}

	static juce::Array<OscillatorType::Value> toArray()
	{
		juce::Array<OscillatorType::Value> oscillatorTypeArray;
		for (int i = ( int ) OscillatorType::firstValue; i <= ( int ) OscillatorType::lastValue; i++)
		{
			auto tmp = OscillatorType::fromInt(i);
			oscillatorTypeArray.add(tmp);
		}
		return oscillatorTypeArray;
	}

	static juce::StringArray toStringArray()
	{
		juce::StringArray oscillatorTypeStringArray;

		std::for_each(OscillatorType::toArray().begin(), OscillatorType::toArray().end(),
					  [&oscillatorTypeStringArray](OscillatorType::Value oscillatorType) {
						  oscillatorTypeStringArray.add(toString(oscillatorType));
					  });

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
