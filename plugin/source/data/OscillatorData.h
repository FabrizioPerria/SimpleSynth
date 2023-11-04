#pragma once

#include "JuceHeader.h"
#include "utils/OscillatorType.h"
#include "data/LFOData.h"

class OscillatorData : public juce::dsp::Oscillator<float>
{
  public:
	OscillatorData();
	void setOscillatorType(OscillatorType oscillatorType);
	void setOscillatorFrequency(int midiNoteNumber);
	void setOscillatorLevel(const float level);
	void prepareToPlay(juce::dsp::ProcessSpec &spec);
	void getNextAudioBlock(juce::dsp::AudioBlock<float> &audioBlock);
	void setLFOFrequency(int midiNoteNumber);
	void setLFO(const float frequency, const float depth);

  private:
	juce::dsp::Gain<float> gain;
	LFOData lfo;

	int currentNote;

	bool isPrepared;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorData)
};
