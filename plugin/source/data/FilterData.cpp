#include "data/FilterData.h"

void FilterData::prepareToPlay(juce::dsp::ProcessSpec &spec)
{
	filter.reset();
	filter.prepare(spec);

	isPrepared = true;
}

void FilterData::process(juce::AudioBuffer<float> &buffer)
{
	jassert(isPrepared);

	juce::dsp::AudioBlock<float> audioBlock(buffer);

	filter.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void FilterData::setParameters(const FilterType type, const float cutoff, const float resonance, const float mod)
{
	filter.setType(FilterType::getFilterType(type));
	auto fMod = cutoff * mod;
	fMod = std::clamp(fMod, 20.0f, 20000.0f);
	filter.setCutoffFrequency(fMod);
	filter.setResonance(resonance);
}
