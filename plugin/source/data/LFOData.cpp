#include "data/LFOData.h"
#include "utils/OscillatorType.h"

void LFOData::setParameters(const float frequency, const float depth)
{
	lfoDepth = depth;
	lfo.setFrequency(frequency);
}

void LFOData::prepare(juce::dsp::ProcessSpec &spec)
{
	lfo.initialise(OscillatorType::getFunction(OscillatorType::SINE));
	lfo.prepare(spec);

	isPrepared = true;
}

float LFOData::getFrequency()
{
	return lfoFreq;
}

void LFOData::process(juce::dsp::AudioBlock<float> &audioBlock)
{
	jassert(isPrepared);

	for (auto channel = 0; channel < ( int ) audioBlock.getNumChannels(); ++channel)
	{
		for (auto sample = 0; sample < ( int ) audioBlock.getNumSamples(); ++sample)
		{
			lfoFreq = lfo.processSample(audioBlock.getSample(channel, sample)) * lfoDepth;
		}
	}
}
