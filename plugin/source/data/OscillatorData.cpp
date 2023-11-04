#include "data/OscillatorData.h"
#include "juce_core/system/juce_PlatformDefs.h"
#include "utils/FilterType.h"

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
	gain.prepare(spec);
	lfo.prepare(spec);
	filter.prepare(spec);

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
	jassert(isPrepared);

	lfo.process(audioBlock);
	process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
	filter.process(audioBlock);
	gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void OscillatorData::setOscillatorLevel(const float level)
{
	gain.setGainDecibels(level);
}

void OscillatorData::setLFO(const float frequency, const float depth)
{
	lfo.setParameters(frequency, depth);
	setOscillatorFrequency(currentNote);
}

void OscillatorData::setFilterType(const FilterType type)
{
	filter.setFilterType(type);
}

void OscillatorData::setFilter(const float cutoff, const float resonance)
{
	filter.setParameters(cutoff, resonance);
}
