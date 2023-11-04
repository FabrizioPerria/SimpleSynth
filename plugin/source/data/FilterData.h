#pragma once

#include "JuceHeader.h"
#include "utils/FilterType.h"

class FilterData
{
  public:
	void prepareToPlay(juce::dsp::ProcessSpec &spec);
	void process(juce::dsp::AudioBlock<float> &audioBlock);
	void setParameters(const float cutoff, const float resonance);
	void setFilterType(const FilterType filterType);

  private:
	void reset();
	juce::dsp::StateVariableTPTFilter<float> filter;

	bool isPrepared;
};
