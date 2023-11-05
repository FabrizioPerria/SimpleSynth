#pragma once

#include "JuceHeader.h"

class ReverbData
{
  public:
	ReverbData();
	void prepareToPlay(const juce::dsp::ProcessSpec &spec);
	void process(juce::AudioBuffer<float> &buffer);
	void update(const float wetdry, const float width, const float damping, const float roomSize);

  private:
	juce::dsp::Reverb reverb;

	bool isPrepared;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbData)
};
