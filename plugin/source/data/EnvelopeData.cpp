#include "data/EnvelopeData.h"
#include <cassert>
EnvelopeData::EnvelopeData()
{
}

void EnvelopeData::update(const float attack, const float decay, const float sustain, const float release)
{
	envelope.setParameters(juce::ADSR::Parameters{attack, decay, sustain, release});
}

void EnvelopeData::preparetoPlay(const juce::dsp::ProcessSpec &spec)
{
	envelope.setSampleRate(spec.sampleRate);
	envelope.reset();

	isPrepared = true;
}

void EnvelopeData::process(juce::AudioBuffer<float> &audioBuffer)
{
	assert(isPrepared);

	envelope.applyEnvelopeToBuffer(audioBuffer, 0, audioBuffer.getNumSamples());
}

void EnvelopeData::noteOn()
{
	envelope.reset();
	envelope.noteOn();
}

void EnvelopeData::noteOff()
{
	envelope.noteOff();
}

bool EnvelopeData::isActive()
{
	return envelope.isActive();
}

float EnvelopeData::getNextSample()
{
	return envelope.getNextSample();
}
