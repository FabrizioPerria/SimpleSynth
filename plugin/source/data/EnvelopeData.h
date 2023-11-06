#pragma once

#include "JuceHeader.h"

class EnvelopeData
{
  public:
	EnvelopeData();
	bool isActive();
	void noteOn();
	void noteOff();
	void preparetoPlay(const juce::dsp::ProcessSpec &spec);
	void update(const float attack, const float decay, const float sustain, const float release);
	void process(juce::AudioBuffer<float> &audioBuffer);
	float getNextSample();

  private:
	juce::ADSR envelope;

	bool isPrepared;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeData)
};
