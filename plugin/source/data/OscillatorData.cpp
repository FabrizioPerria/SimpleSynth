#include "data/OscillatorData.h"
#include "juce_core/system/juce_PlatformDefs.h"
#include "utils/FilterType.h"
#include <cassert>

OscillatorData::OscillatorData() : currentNote(0)
{
	setOscillatorType(OscillatorType::SINE);
}

void OscillatorData::setOscillatorType(OscillatorType waveType)
{
	initialise(OscillatorType::getFunction(waveType));
}

void OscillatorData::prepareToPlay(juce::dsp::ProcessSpec &spec)
{
	prepare(spec);
	gain.prepareToPlay(spec);
	lfo.prepare(spec);

	isPrepared = true;
}

void OscillatorData::setOscillatorFrequency(int midiNoteNumber)
{
	setFrequency(
		std::abs(static_cast<float>(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)) + lfo.getFrequency()));
	currentNote = midiNoteNumber;
}

void OscillatorData::getNextAudioBlock(juce::dsp::AudioBlock<float> &audioBlock)
{
	assert(isPrepared);

	lfo.process(audioBlock);
	process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
	gain.process(audioBlock);
}

void OscillatorData::setOscillatorLevel(const float level)
{
	gain.setGain(level);
}

void OscillatorData::setLFO(const float frequency, const float depth)
{
	lfo.setParameters(frequency, depth);
	setOscillatorFrequency(currentNote);
}
