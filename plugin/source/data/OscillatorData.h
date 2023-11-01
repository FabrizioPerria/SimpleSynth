#pragma once

#include "JuceHeader.h"
#include "utils/OscillatorType.h"

class OscillatorData : public juce::dsp::Oscillator<float>
{
  public:
	void setOscillatorType(OscillatorType oscillatorType);

  private:
	juce::dsp::Gain<float> gain;
};
