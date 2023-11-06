#include "data/GainData.h"
#include <cassert>

void GainData::prepareToPlay(juce::dsp::ProcessSpec &spec)
{
	gain.reset();
	gain.prepare(spec);

	isPrepared = true;
}

void GainData::process(juce::AudioBuffer<float> &buffer)
{
	juce::dsp::AudioBlock<float> block(buffer);
	process(block);
}

void GainData::process(juce::dsp::AudioBlock<float> &block)
{
	assert(isPrepared);
	gain.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void GainData::setGain(const float gainValue)
{
	gain.setGainDecibels(gainValue);
}
