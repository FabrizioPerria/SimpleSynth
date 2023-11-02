#pragma once

#include "JuceHeader.h"

class EnvelopeData : public juce::ADSR
{
  public:
	void preparetoPlay(const juce::dsp::ProcessSpec &spec);
	void update(const float attack, const float decay, const float sustain, const float release);

  private:
	juce::ADSR::Parameters envelopeParameters;
};
