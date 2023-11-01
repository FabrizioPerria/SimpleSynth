#include "data/OscillatorData.h"

void OscillatorData::setOscillatorType(OscillatorType waveType)
{
	switch (waveType)
	{
	case OscillatorType::SINE:
		initialise([](float x) { return std::sin(x); });
		break;
	case OscillatorType::SQUARE:
		initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; });
		break;
	case OscillatorType::SAW:
		initialise([](float x) { return x / juce::MathConstants<float>::pi; });
		break;
	default:
		jassertfalse;
		break;
	}
}
