#pragma once

#include "JuceHeader.h"
#include "data/EnvelopeData.h"
#include "utils/FilterType.h"

class FilterData
{
  public:
	void prepareToPlay(juce::dsp::ProcessSpec &spec);
	void process(juce::AudioBuffer<float> &buffer);
	void setParameters(const FilterType type, const float cutoff, const float resonance, const float mod = 1.0f);
	void setFilterType(const FilterType filterType);

  private:
	juce::dsp::StateVariableTPTFilter<float> filter;

	bool isPrepared;
};
