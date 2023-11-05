#include "data/ReverbData.h"
#include "BinaryData.h"

ReverbData::ReverbData()
{
}

void ReverbData::prepareToPlay(const juce::dsp::ProcessSpec &spec)
{
	reverb.reset();
	reverb.prepare(spec);

	isPrepared = true;
}

void ReverbData::process(juce::AudioBuffer<float> &buffer)
{
	jassert(isPrepared);

	juce::dsp::AudioBlock<float> audioBlock(buffer);
	reverb.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void ReverbData::update(const float wetdry, const float width, const float damping, const float roomSize)
{
	juce::dsp::Reverb::Parameters parameters;
	parameters.wetLevel = wetdry;
	parameters.dryLevel = 1.0f - wetdry;
	parameters.width = width;
	parameters.damping = damping;
	parameters.roomSize = roomSize;
	reverb.setParameters(parameters);
}
