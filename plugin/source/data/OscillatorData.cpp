#include "data/OscillatorData.h"

OscillatorData::OscillatorData() : lfoDepth(0.0f), fmMod(0.0f), currentNote(0)
{
	setOscillatorType(OscillatorType::SINE);
	lfo.initialise(OscillatorType::getFunction(OscillatorType::SINE));
}

void OscillatorData::setOscillatorType(OscillatorType waveType)
{
	initialise(OscillatorType::getFunction(waveType));
}

void OscillatorData::prepareToPlay(juce::dsp::ProcessSpec &spec)
{
	prepare(spec);
	gain.prepare(spec);
	lfo.prepare(spec);
}

void OscillatorData::setOscillatorFrequency(int midiNoteNumber)
{
	setFrequency(std::abs(static_cast<float>(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)) + fmMod));
	currentNote = midiNoteNumber;
}

void OscillatorData::getNextAudioBlock(juce::dsp::AudioBlock<float> &audioBlock)
{
	for (auto channel = 0; channel < ( int ) audioBlock.getNumChannels(); ++channel)
	{
		for (auto sample = 0; sample < ( int ) audioBlock.getNumSamples(); ++sample)
		{
			fmMod = lfo.processSample(audioBlock.getSample(channel, sample)) * lfoDepth;
		}
	}
	process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
	gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void OscillatorData::setOscillatorLevel(const float level)
{
	gain.setGainDecibels(level);
}

void OscillatorData::setLFO(const float frequency, const float depth)
{
	lfo.setFrequency(frequency);
	lfoDepth = depth;
	setOscillatorFrequency(currentNote);
}
