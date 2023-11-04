#pragma once

#include "JuceHeader.h"

class LFOData
{
  public:
	void setParameters(const float frequency, const float depth);
	void prepare(juce::dsp::ProcessSpec &spec);
	float getFrequency();
	void process(juce::dsp::AudioBlock<float> &audioBlock);

  private:
	juce::dsp::Oscillator<float> lfo;
	float lfoDepth;
	float lfoFreq;

	bool isPrepared;
};
