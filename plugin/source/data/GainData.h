#pragma once

#include "JuceHeader.h"

class GainData
{
  public:
	void prepareToPlay(juce::dsp::ProcessSpec &spec);
	void process(juce::AudioBuffer<float> &buffer);
	void process(juce::dsp::AudioBlock<float> &block);
	void setGain(const float gain);

  private:
	juce::dsp::Gain<float> gain;

	bool isPrepared;
};
