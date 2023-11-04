#pragma once

#include "JuceHeader.h"
#include "data/FilterData.h"
#include "utils/OscillatorType.h"
#include "utils/FilterType.h"
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
	void setFilterType(const FilterType filterType);
	void setFilter(const float cutoff, const float resonance);

  private:
	juce::dsp::Gain<float> gain;
	LFOData lfo;
	FilterData filter;

	int currentNote;

	bool isPrepared;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorData)
};
