#pragma once

#include "JuceHeader.h"
#include "utils/OscillatorType.h"

class OscillatorData : public juce::dsp::Oscillator<float>
{
  public:
	void setOscillatorType(OscillatorType oscillatorType);
	void setOscillatorFrequency(int midiNoteNumber);
	void setOscillatorLevel(const float level);
	void prepareToPlay(juce::dsp::ProcessSpec &spec);
	void getNextAudioBlock(juce::dsp::AudioBlock<float> &audioBlock);

  private:
	juce::dsp::Gain<float> gain;
};
