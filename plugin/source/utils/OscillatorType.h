#pragma once

#include "JuceHeader.h"
#include <functional>
#include "utils/SVGData.h"
#include <cassert>
class OscillatorType
{
  public:
	enum Value
	{
		firstValue,
		SINE = firstValue,
		SQUARE,
		TRIANGLE,
		SAW,
		lastValue = SAW
	};

	static std::function<float(float)> getFunction(OscillatorType::Value oscillatorType)
	{
		switch (oscillatorType)
		{
		case OscillatorType::SINE:
			return [](float x) { return std::sin(x); };
		case OscillatorType::SQUARE:
			return [](float x) { return x < 0.0f ? -1.0f : 1.0f; };
		case OscillatorType::TRIANGLE:
			return [](float x) { return std::acos(std::sin(x)) / juce::MathConstants<float>::halfPi; };
		case OscillatorType::SAW:
			return [](float x) { return x / juce::MathConstants<float>::pi; };
		default:
			assert(false);
			return [](float x) { return x; };
		}
	}

	static juce::String toString(OscillatorType::Value oscillatorType)
	{
		switch (oscillatorType)
		{
		case OscillatorType::SINE:
			return "Sine";
		case OscillatorType::SQUARE:
			return "Square";
		case OscillatorType::TRIANGLE:
			return "Triangle";
		case OscillatorType::SAW:
			return "Saw";
		default:
			assert(false);
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
		case OscillatorType::TRIANGLE:
			return SVGData{BinaryData::triangle_svg, BinaryData::triangle_svgSize};
		case OscillatorType::SAW:
			return SVGData{BinaryData::sawtooth_svg, BinaryData::sawtooth_svgSize};
		default:
			assert(false);
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

		for (auto type : OscillatorType::toArray())
		{
			oscillatorTypeStringArray.add(toString(type));
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
		auto isIntValid = (i >= static_cast<int>(OscillatorType::firstValue) && i <= static_cast<int>(Value::lastValue));
		assert(isIntValid);
		return static_cast<Value>(i);
	}

  private:
	Value value;
};
