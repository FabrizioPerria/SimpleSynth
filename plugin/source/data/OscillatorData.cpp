#include "data/OscillatorData.h"

void OscillatorData::setOscillatorType(OscillatorType waveType)
{
	initialise(OscillatorType::getFunction(waveType));
}

void OscillatorData::prepareToPlay(juce::dsp::ProcessSpec &spec)
{
	prepare(spec);
}

void OscillatorData::setOscillatorFrequency(int midiNoteNumber)
{
	setFrequency(static_cast<float>(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)));
}

void OscillatorData::getNextAudioBlock(juce::dsp::AudioBlock<float> &audioBlock)
{
	process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}
