#include "SynthVoice.h"
#include "SynthSound.h"

bool SynthVoice::canPlaySound(SynthesiserSound *sound)
{
	return isPrepared && dynamic_cast<SynthSound *>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
{
	juce::ignoreUnused(velocity);
	juce::ignoreUnused(sound);
	juce::ignoreUnused(currentPitchWheelPosition);
	envelope.noteOn();
	osc.setFrequency(static_cast<float>(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)));
}
void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
	juce::ignoreUnused(velocity);
	juce::ignoreUnused(allowTailOff);
	envelope.noteOff();
}
void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
	juce::ignoreUnused(newPitchWheelValue);
}
void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
	juce::ignoreUnused(controllerNumber);
	juce::ignoreUnused(newControllerValue);
}

void SynthVoice::renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
	jassert(isPrepared);
	juce::dsp::AudioBlock<float> audioBlock{outputBuffer};
	osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
	gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
	envelope.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels)
{
	dsp::ProcessSpec spec;
	spec.sampleRate = sampleRate;
	spec.maximumBlockSize = ( uint32_t ) samplesPerBlock;
	spec.numChannels = ( uint32_t ) numOutputChannels;

	osc.prepare(spec);

	gain.setGainLinear(0.01f);
	gain.prepare(spec);

	envelope.setSampleRate(sampleRate);

	isPrepared = true;
}
