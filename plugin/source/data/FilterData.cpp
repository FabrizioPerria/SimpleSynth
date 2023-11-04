#include "data/FilterData.h"

void FilterData::prepareToPlay(juce::dsp::ProcessSpec &spec)
{
	filter.reset();
	filter.prepare(spec);

	isPrepared = true;
}

void FilterData::process(juce::dsp::AudioBlock<float> &audioBlock)
{
	jassert(isPrepared);

	filter.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void FilterData::setParameters(const float cutoff, const float resonance)
{
	filter.setCutoffFrequency(cutoff);
	filter.setResonance(resonance);
}

void FilterData::setFilterType(const FilterType type)
{
	filter.setType(FilterType::getFilterType(type));
}

void FilterData::reset()
{
	filter.reset();
}
